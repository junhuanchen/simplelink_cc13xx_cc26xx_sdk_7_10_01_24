/******************************************************************************

 @file  iot_ble_hal_mq_task.c

 @brief Task used to process asychronous ICall messages.

 Group: WCS, LPC
 Target Device: cc13xx_cc26xx

 ******************************************************************************

 Copyright (c) 2023, Texas Instruments Incorporated

 All rights reserved not granted herein.
 Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free,
 non-exclusive license under copyrights and patents it now or hereafter
 owns or controls to make, have made, use, import, offer to sell and sell
 ("Utilize") this software subject to the terms herein. With respect to the
 foregoing patent license, such license is granted solely to the extent that
 any such patent is necessary to Utilize the software alone. The patent
 license shall not apply to any combinations which include this software,
 other than combinations with devices manufactured by or for TI ("TI
 Devices"). No hardware patent is licensed hereunder.

 Redistributions must preserve existing copyright notices and reproduce
 this license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution.

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

   * No reverse engineering, decompilation, or disassembly of this software
     is permitted with respect to any software provided in binary form.
   * Any redistribution and use are licensed by TI for use only with TI Devices.
   * Nothing shall obligate TI to provide you with source code for the software
     licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution
 of the source code are permitted provided that the following conditions are
 met:

   * Any redistribution and use of the source code, including any resulting
     derivative works, are licensed by TI for use only with TI Devices.
   * Any redistribution and use of any object code compiled from the source
     code and any resulting derivative works, are licensed by TI for use
     only with TI Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this
 software without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************


 *****************************************************************************/

/**
 * @file iot_ble_hal_mq_task.c
 * @brief Task used to process asychronous ICall messages
 */

/* POSIX Include files */
#include <mqueue.h>
#include <semaphore.h>
#include <time.h>

/* FreeRTOS related includes */
#include "FreeRTOS.h"
#include "task.h"
#include <queue.h>

/* ICall and BLE-Stack */
#include <bcomdef.h>
#include <icall.h>
#include "util.h"
/* BLE-Stack API definitions: Must be the last file in list of stack includes */
#include <icall_ble_api.h>

/* BLE HAL related files */
#include "bt_hal_manager.h"
#include "bt_hal_manager_adapter_ble.h"
#include "iot_ble_hal_mq_task.h"
#include "iot_ble_hal_internals.h"

/*-----------------------------------------------------------*/

#define BLE_HAL_MQ_TASK_STACK_SIZE        ( configMINIMAL_STACK_SIZE )
#define BLE_HAL_MQ_STACK_PRIORITY         ( 5U )

#define TX_PDU_SIZE (27)
#define RX_PDU_SIZE (27)
#define TX_TIME     (328)
#define RX_TIME     (328)
#define  PAL_ADV_TERMINATED_CB_EVENT 0x70000000

/*-----------------------------------------------------------*/
#ifdef GAP_BOND_MGR
static void _passcodeCB( uint8_t *deviceAddr,
                         uint16_t connHandle,
                         uint8_t uiInputs,
                         uint8_t uiOutputs,
                         uint32_t numComparison );

static void _pairStateCB( uint16_t connHandle,
                          uint8_t state,
                          uint8_t status );
#endif
static bool _processStackMsg( ICall_Hdr * pxMsg );
static void _processGapMsg( gapEventHdr_t * pxMsg );
static void _processGattMsg( gattMsgEvent_t *pxMsg );
static void _taskFxn( void * pvParameters );
static void _taskInit( void );

/*-----------------------------------------------------------*/

/* Entity ID globally used to check for source and/or destination of messages */
static ICall_EntityID xSelfEntity = ICALL_INVALID_ENTITY_ID;

/* ICall events used to pend and post system and local events */
static ICall_SyncHandle xSyncHandle = NULL;

/* Semaphore used to indicate that data must be processed */
static sem_t xTaskInitSem;

/* Handle of the MQ task */
static TaskHandle_t xTaskHandle = NULL;

/* Address of connected device */
BTBdaddr_t xPeerBTAddr;

#ifdef GAP_BOND_MGR
/* GAP Bond Manager Callbacks */
static gapBondCBs_t xBondMgrCBs =
{
  _passcodeCB,        /* Passcode callback */
  _pairStateCB        /* Pairing state callback */
};
#endif

extern QueueHandle_t xAdvStateQueue;
extern QueueHandle_t xConnStateQueue;
extern uint16_t l2capMtuSize;
extern void (*ti_ble_adapter_adv_terminated_cb)(void);

/*-----------------------------------------------------------*/

static void _taskInit( void )
{
    /* NO STACK API CALLS CAN OCCUR BEFORE THIS CALL TO ICall_registerApp
     * Register the current thread as an ICall dispatcher application
     * so that the application can send and receive messages.
     */
    if( xSelfEntity == ICALL_INVALID_ENTITY_ID )
    {
       ICall_registerApp( &xSelfEntity, &xSyncHandle );
    }
#ifdef GAP_BOND_MGR
    /* Start Bond Manager and register callbacks */
    GAPBondMgr_Register( &xBondMgrCBs );
#endif

    /* Register with GAP for HCI/Host messages. Needed to receive HCI events */
    GAP_RegisterForMsgs( xSelfEntity );
}

/*-----------------------------------------------------------*/
static void _taskFxn( void * pvParameters )
{
    /* Initialize the stack and register the thread with ICall */
    _taskInit();

    /* Post the semaphore to notify that the the task has initialized */
    sem_post( &xTaskInitSem );

    for ( ;; )
    {
        uint32_t ulEvents;

        /* Waits for an event to be posted associated with the calling thread.
         * Note that an event associated with a thread is posted when a
         * message is queued to the message receive queue of the thread
         */
        mq_receive( xSyncHandle, (char*)&ulEvents, sizeof(uint32_t), NULL );
        if (ulEvents == PAL_ADV_TERMINATED_CB_EVENT && ti_ble_adapter_adv_terminated_cb != NULL)
        {
            (*ti_ble_adapter_adv_terminated_cb)();
        }
        else /* ulEvent = 0x80000000 is used by Icall_Signal */
        {
            ICall_EntityID xDest;
            ICall_ServiceEnum xSrc;
            ICall_HciExtEvt *pxMsg = NULL;
            ICall_Errno xIcallStatus = ICall_fetchServiceMsg( &xSrc,
                                                              &xDest,
                                                              (void **)&pxMsg );

            if ( xIcallStatus == ICALL_ERRNO_SUCCESS )
            {
                bool bSafeToDealloc = true;

                if ( ( xSrc == ICALL_SERVICE_CLASS_BLE ) &&
                     ( xDest == xSelfEntity ) )
                {
                    ICall_Stack_Event *pxEvt = (ICall_Stack_Event *)pxMsg;

                    /* Check for BLE stack events */
                    if ( pxEvt->signature != 0xffff )
                    {
                        /* Process stack-to-app message */
                        bSafeToDealloc = _processStackMsg( (ICall_Hdr *)pxMsg );
                    }
                }

                if ( pxMsg && bSafeToDealloc )
                {
                    ICall_freeMsg( pxMsg );
                }
            }
        }

    }
}

/*-----------------------------------------------------------*/

static bool _processStackMsg( ICall_Hdr *pxMsg )
{
bool bSafeToDealloc = TRUE;

    switch (pxMsg->event)
    {
        case GAP_MSG_EVENT:
            _processGapMsg( (gapEventHdr_t*) pxMsg );
            break;

        case GATT_MSG_EVENT:
            _processGattMsg( (gattMsgEvent_t *) pxMsg);
            break;

        case HCI_GAP_EVENT_EVENT:
        {
            switch (pxMsg->status)
            {
                case HCI_COMMAND_COMPLETE_EVENT_CODE:
                    break;

                case HCI_BLE_HARDWARE_ERROR_EVENT_CODE:
                    break;

                case HCI_COMMAND_STATUS_EVENT_CODE:
                {
                    hciEvt_CommandStatus_t *pxMyMsg = (hciEvt_CommandStatus_t *)pxMsg;
                    switch ( pxMyMsg->cmdOpcode )
                    {
                    case HCI_LE_SET_PHY:
                        break;
                    case HCI_DISCONNECT:
                        break;

                    default:
                        break;
                    }
                    break;
                }
                case HCI_LE_EVENT_CODE:
                {
                    break;
                }

                default:
                    break;
            }

            break;
        }

        case L2CAP_SIGNAL_EVENT:
            break;

        default:
            break;
    }

  return ( bSafeToDealloc );
}

/*-----------------------------------------------------------*/

static void _processGapMsg( gapEventHdr_t *pxMsg )
{

    if(pxMsg == NULL)
    {
        return;
    }

    switch ( pxMsg->opcode )
    {
        case GAP_DEVICE_INIT_DONE_EVENT:
        {
            gapDeviceInitDoneEvent_t *pxPkt = ( gapDeviceInitDoneEvent_t * ) pxMsg;
            if( _xBTCallbacks.pxDeviceStateChangedCb != NULL )
            {
                _xBTCallbacks.pxDeviceStateChangedCb( eBTstateOn );
            }

            /* Data length extension is not needed or used, set lower defaults
             * in order to save heap memory
             */
            HCI_EXT_SetMaxDataLenCmd( TX_PDU_SIZE,
                                      TX_TIME,
                                      RX_PDU_SIZE,
                                      RX_TIME );

            vProcessGapDeviceInit(pxPkt);

            break;
        }
        case GAP_LINK_ESTABLISHED_EVENT:
        {
            gapEstLinkReqEvent_t *pxPkt = ( gapEstLinkReqEvent_t * ) pxMsg;
            uint32_t ulAdvEvent = 0;

            if( pxPkt->hdr.status == SUCCESS )
            {
                /* Copy the device address into local memory */
                memcpy(xPeerBTAddr.ucAddress, pxPkt->devAddr, btADDRESS_LEN);

                if( _xGattServerCallbacks.pxConnectionCb )
                {
                    _xGattServerCallbacks.pxConnectionCb( pxPkt->connectionHandle,
                                                          ulGattServerIFhandle,
                                                          true,
                                                          &xPeerBTAddr );
                }

                ICall_EntityID xEntity = _IotBleHalAsyncMq_GetEntity();
                attExchangeMTUReq_t msg;
                msg.clientRxMTU = l2capMtuSize;
                GATT_ExchangeMTU(pxPkt->connectionHandle, &msg, xEntity);
            }

            break;
        }

        case GAP_LINK_TERMINATED_EVENT:
        {
            gapTerminateLinkEvent_t *pxPkt = ( gapTerminateLinkEvent_t * ) pxMsg;

            if( vGetDeInitStatus() == true )
            {
                uint32_t event = GAP_LINK_TERMINATED_EVENT;
                /* Send notice to application task */
                if( xConnStateQueue != NULL)
                {
                    xQueueSendFromISR( xConnStateQueue, ( void * ) &event, NULL );
                }
            }

            if( _xGattServerCallbacks.pxConnectionCb )
            {
                _xGattServerCallbacks.pxConnectionCb( pxPkt->connectionHandle,
                                                      ulGattServerIFhandle,
                                                      false,
                                                      &xPeerBTAddr );
            }
            uint16_t rpaTimeoutInterval = 15;
            GAP_SetParamValue(GAP_PARAM_PRIVATE_ADDR_INT, rpaTimeoutInterval);
            break;
        }

        default:
            break;
    }
}

/*-----------------------------------------------------------*/

static void _processGattMsg( gattMsgEvent_t *pxMsg )
{

    if(pxMsg == NULL)
    {
        return;
    }

    if ( linkDB_Up( pxMsg->connHandle ) )
    {
        switch ( pxMsg->method )
        {
            case ATT_MTU_UPDATED_EVENT:
            {
                if( _xGattServerCallbacks.pxMtuChangedCb )
                {
                    _xGattServerCallbacks.pxMtuChangedCb( pxMsg->connHandle,
                                                          pxMsg->msg.mtuEvt.MTU );
                }
                break;
            }
            case ATT_HANDLE_VALUE_IND:
            {
                /* Send confirm for indication */
                ATT_HandleValueCfm( pxMsg->connHandle );
                break;
            }

            default:
                break;
        }
    }

  /* Free message payload. Needed only for ATT Protocol messages */
  GATT_bm_free(&pxMsg->msg, pxMsg->method);
}

#ifdef GAP_BOND_MGR
/*-----------------------------------------------------------*/

static void _passcodeCB( uint8_t *deviceAddr,
                           uint16_t connHandle,
                           uint8_t uiInputs,
                           uint8_t uiOutputs,
                           uint32_t numComparison )
{

}

/*-----------------------------------------------------------*/

static void _pairStateCB( uint16_t connHandle,
                            uint8_t state,
                            uint8_t status )
{

}
#endif

/*-----------------------------------------------------------*/

BTStatus_t _IotBleHalAsyncMq_CreateTask( void )
{
    static bool bTaskExists = false;
    uint32_t lCurrentThreadPriority;
    BaseType_t xRetVal;
    int lSemStatus = 0;

    /* Guard against creating the task many times */
    if( bTaskExists  == (bool)true )
    {
        return ( eBTStatusDone );
    }

    lSemStatus = sem_init( &xTaskInitSem, 0, 0 );
    if (lSemStatus == -1)
    {
        return ( eBTStatusFail );
    }

    /* Get the priority of the currently executing user thread. We use this
     * to set the priority of the proxy task below.
     */
    lCurrentThreadPriority = uxTaskPriorityGet( xTaskGetCurrentTaskHandle() );

    /* The stack proxy task should have priority that is greater than the
     * currently running user thread, but lower than that of the ICall thread.
     *
     * The reason for having a proxy task is so that it can check and service
     * asynchronous messages from the stack in the ICall message queue.
     */
    if( lCurrentThreadPriority + 1 < BLE_HAL_MQ_STACK_PRIORITY )
    {
        lCurrentThreadPriority++;
    }
    else
    {
        return ( eBTStatusParamInvalid );
    }

    xRetVal = xTaskCreate( _taskFxn,
                            "ICall Message Queue Thread",
                            BLE_HAL_MQ_TASK_STACK_SIZE,
                            NULL,
                            lCurrentThreadPriority,
                            &xTaskHandle );

    if( xRetVal != pdPASS  )
    {
        /* Task creation failed */
        return ( eBTStatusFail );
    }

    /* Wait for transaction ready for treatment */
    lSemStatus = sem_wait( &xTaskInitSem );
    if ( lSemStatus == -1 )
    {
        return ( eBTStatusFail );
    }

    bTaskExists = (bool)true;
    return ( eBTStatusSuccess );
}

/*-----------------------------------------------------------*/

void _IotBleHalAsyncMq_DestroyTask( void )
{
    vTaskDelete( xTaskHandle );

    sem_destroy( &xTaskInitSem );
}
/*-----------------------------------------------------------*/

ICall_EntityID _IotBleHalAsyncMq_GetEntity( void )
{
    return ( xSelfEntity );
}

/*-----------------------------------------------------------*/

void _postPALAdvTermEventToICallTask( void )
{
    uint32_t pal_event = PAL_ADV_TERMINATED_CB_EVENT;
    mq_send(xSyncHandle,(char*)&pal_event,sizeof(pal_event),1);
}

/*-----------------------------------------------------------*/
