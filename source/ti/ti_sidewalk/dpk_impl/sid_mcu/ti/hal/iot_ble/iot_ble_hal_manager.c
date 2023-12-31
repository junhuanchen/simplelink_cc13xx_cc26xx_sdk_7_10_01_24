/******************************************************************************

 @file  iot_ble_hal_manager.c

 @brief Hardware Abstraction Layer for GAP ble stack.

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
 * @file iot_bt_hal_manager.c
 * @brief Hardware Abstraction Layer for GAP ble stack.
 */

/* FreeRTOS includes */
#include <FreeRTOS.h>
#include <queue.h>

/* BLE-Stack Middleware (e.g. HAL, ICall) */
#include <icall.h>
/* BLE-Stack user configuration settings */
#include "ble_user_config.h"
#include "ti_ble_config.h"
/* Buffer get implementation */
#include <bget.h>
/* BLE-Stack API definitions: Must be the last file in list of stack includes */
#include <icall_ble_api.h>

/* BLE HAL related files */
#include "bt_hal_manager_adapter_ble.h"
#include "bt_hal_manager.h"
#include "bt_hal_gatt_server.h"
#include "iot_ble_hal_internals.h"

/* C standard library includes */
#include <string.h>
#include <stdlib.h>

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTManagerInit( const BTCallbacks_t * pxCallbacks );
static BTStatus_t _prvBtManagerCleanup( void );
static BTStatus_t _prvBTEnable( uint8_t ucGuestMode );
static BTStatus_t _prvBTDisable();
static BTStatus_t _prvBTGetAllDeviceProperties();
static BTStatus_t _prvBTGetDeviceProperty( BTPropertyType_t xType );
static BTStatus_t _prvBTSetDeviceProperty( const BTProperty_t * pxProperty );
static BTStatus_t _prvBTGetAllRemoteDeviceProperties( BTBdaddr_t * pxRemoteAddr );
static BTStatus_t _prvBTGetRemoteDeviceProperty( BTBdaddr_t * pxRemoteAddr,
                                                 BTPropertyType_t type );
static BTStatus_t _prvBTSetRemoteDeviceProperty( BTBdaddr_t * pxRemoteAddr,
                                                 const BTProperty_t * property );
static BTStatus_t _prvBTPair( const BTBdaddr_t * pxBdAddr,
                              BTTransport_t xTransport,
                              bool bCreateBond );
static BTStatus_t _prvBTCreateBondOutOfBand( const BTBdaddr_t * pxBdAddr,
                                             BTTransport_t xTransport,
                                             const BTOutOfBandData_t * pxOobData );
static BTStatus_t _prvBTCancelBond( const BTBdaddr_t * pxBdAddr );
static BTStatus_t _prvBTRemoveBond( const BTBdaddr_t * pxBdAddr );
static BTStatus_t _prvBTGetConnectionState( const BTBdaddr_t * pxBdAddr,
                                            bool * bConnectionState );
static BTStatus_t _prvBTPinReply( const BTBdaddr_t * pxBdAddr,
                                  uint8_t ucAccept,
                                  uint8_t ucPinLen,
                                  BTPinCode_t * pxPinCode );
static BTStatus_t _prvBTSspReply( const BTBdaddr_t * pxBdAddr,
                                  BTSspVariant_t xVariant,
                                  uint8_t ucAccept,
                                  uint32_t ulPasskey );
static BTStatus_t _prvBTReadEnergyInfo();
static BTStatus_t _prvBTDutModeConfigure( bool bEnable );
static BTStatus_t _prvBTDutModeSend( uint16_t usOpcode,
                                     uint8_t * pucBuf,
                                     size_t xLen );
static BTStatus_t _prvBTLeTestMode( uint16_t usOpcode,
                                    uint8_t * pucBuf,
                                    size_t xLen );
static BTStatus_t _prvBTConfigHCISnoopLog( bool bEnable );
static BTStatus_t _prvBTConfigClear();
static BTStatus_t _prvBTReadRssi( const BTBdaddr_t * pxBdAddr );
static BTStatus_t _prvBTGetTxpower( const BTBdaddr_t * pxBdAddr,
                                    BTTransport_t xTransport );
static const void * _prvGetClassicAdapter();
static void _prvAssertHandler(uint8_t ucAssertCause, uint8_t ucAssertSubcause);

/*-----------------------------------------------------------*/

/* Entity ID globally used to check for source and/or destination of messages */
static ICall_EntityID _xUserTaskEntity;

/* ICall events used to pend and post system and local events */
static ICall_SyncHandle _xUserTaskSyncEvent;

static BTInterface_t xBTinterface =
{
    .pxBtManagerInit                = _prvBTManagerInit,
    .pxBtManagerCleanup             = _prvBtManagerCleanup,
    .pxEnable                       = _prvBTEnable,
    .pxDisable                      = _prvBTDisable,
    .pxGetAllDeviceProperties       = _prvBTGetAllDeviceProperties,
    .pxGetDeviceProperty            = _prvBTGetDeviceProperty,
    .pxSetDeviceProperty            = _prvBTSetDeviceProperty,
    .pxGetAllRemoteDeviceProperties = _prvBTGetAllRemoteDeviceProperties,
    .pxGetRemoteDeviceProperty      = _prvBTGetRemoteDeviceProperty,
    .pxSetRemoteDeviceProperty      = _prvBTSetRemoteDeviceProperty,
    .pxPair                         = _prvBTPair,
    .pxCreateBondOutOfBand          = _prvBTCreateBondOutOfBand,
    .pxCancelBond                   = _prvBTCancelBond,
    .pxRemoveBond                   = _prvBTRemoveBond,
    .pxGetConnectionState           = _prvBTGetConnectionState,
    .pxPinReply                     = _prvBTPinReply,
    .pxSspReply                     = _prvBTSspReply,
    .pxReadEnergyInfo               = _prvBTReadEnergyInfo,
    .pxDutModeConfigure             = _prvBTDutModeConfigure,
    .pxDutModeSend                  = _prvBTDutModeSend,
    .pxLeTestMode                   = _prvBTLeTestMode,
    .pxConfigHCISnoopLog            = _prvBTConfigHCISnoopLog,
    .pxConfigClear                  = _prvBTConfigClear,
    .pxReadRssi                     = _prvBTReadRssi,
    .pxGetTxpower                   = _prvBTGetTxpower,
    .pxGetClassicAdapter            = _prvGetClassicAdapter,
    .pxGetLeAdapter                 = _prvGetLeAdapter,
};

/*-----------------------------------------------------------*/

extern uint16_t l2capMtuSize;

extern assertCback_t halAssertCback;

/*-----------------------------------------------------------*/

BTCallbacks_t _xBTCallbacks;

/*-----------------------------------------------------------*/

#ifdef ICALL_JT
    icall_userCfg_t user0Cfg = BLE_USER_CFG;
#else
    bleUserCfg_t user0Cfg = BLE_USER_CFG;
#endif /* ICALL_JT */

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTManagerInit( const BTCallbacks_t * pxCallbacks )
{
    BTStatus_t xStatus = eBTStatusSuccess;
    static bool bIsInitialized = false;

    /* Protect that initialization completes without interrupt */
    vPortEnterCritical();

    if( (pxCallbacks != NULL)  && (bIsInitialized == false))
    {
        _xBTCallbacks = *pxCallbacks;

        /* Register Application callback to trap asserts raised in the Stack */
        halAssertCback = _prvAssertHandler;

        user0Cfg.appServiceInfo->timerTickPeriod = ICall_getTickPeriod();
        user0Cfg.appServiceInfo->timerMaxMillisecond  = ICall_getMaxMSecs();

        /* Initialize ICall module */
        ICall_init();

        /* Start tasks of external images - highest priority */
        ICall_createRemoteTasks();

        /* NO STACK API CALLS CAN OCCUR BEFORE THIS CALL TO ICall_registerApp
        *
        * The current thread is only registered with ICall to provide API
        * synchronization. The async message queue is managed by the
        * proxy task created by BleHal_createTask()
        */
        ICall_registerApp( &_xUserTaskEntity, &_xUserTaskSyncEvent );

        bIsInitialized = true;
    }

    vPortExitCritical();


    return ( xStatus );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBtManagerCleanup()
{
    BTStatus_t xStatus = eBTStatusSuccess;
    xBTCleanUp();

    return ( xStatus );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTEnable( uint8_t ucGuestMode )
{
  BTStatus_t xStatus = _IotBleHalAsyncMq_CreateTask();
  uint8_t xStackStatus = SUCCESS;

  if(( xStatus != eBTStatusSuccess ) && ( xStatus != eBTStatusDone ))
  {
    return xStatus;
  }

  if( vGetGapStatus() == false )
  {
    GATT_InitClient("");
    /* Initialize GAP layer for peripheral, asynch events are routed
     * to the proxy task
     */
    xStackStatus = GAP_DeviceInit( GAP_PROFILE_PERIPHERAL,
                                  _IotBleHalAsyncMq_GetEntity(),
                                  ADDRMODE_RP_WITH_PUBLIC_ID,
                                  NULL );

    xStatus = _IotBleHalTypes_ConvertStatus( xStackStatus );
  }
  else
  {
    /* re-enable BLE RF */
    GAP_ReInit("");

    /* Create the advertising set */
    xStatus = vCreateAdvSet();
  }
  return ( xStatus );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTDisable()
{
    BTStatus_t xStatus = eBTStatusSuccess;

    xStatus = xBTStop();

    return ( xStatus );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTGetAllDeviceProperties()
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTGetDeviceProperty( BTPropertyType_t xType )
{
    BTStatus_t xStatus = eBTStatusSuccess;
    bStatus_t  xStackStatus = SUCCESS;
    BTProperty_t xReturnedProperty;

    if( _xBTCallbacks.pxAdapterPropertiesCb != NULL )
    {
        xReturnedProperty.xType = xType;

        switch( xType )
        {
            case eBTpropertyBdname:
            {
                /* It is the callback consumer's responsibility to copy the
                 * data so it is safe to use a local variable to hold the device
                 * name.
                 */
                uint8_t ucDeviceName[ GAP_DEVICE_NAME_LEN ];

                /* Note that the stack **requires** a buffer of
                 * GAP_DEVICE_NAME_LEN to be passed into the get param function
                 */
                xStackStatus = GGS_GetParameter( GGS_DEVICE_NAME_ATT,
                                                 &ucDeviceName );
                xStatus = _IotBleHalTypes_ConvertStatus( xStackStatus );

                xReturnedProperty.xLen = strlen ( ( const char *)ucDeviceName );

                /* Set an upper bound on the strlen to prevent memory issues
                 * related to string overrun
                 */
                if( xReturnedProperty.xLen > GAP_DEVICE_NAME_LEN )
                {
                    xStatus = eBTStatusFail;
                    xReturnedProperty.pvVal = NULL;
                }
                else
                {
                    xReturnedProperty.pvVal = &ucDeviceName;
                }

                _xBTCallbacks.pxAdapterPropertiesCb( eBTStatusSuccess,
                                                     1,
                                                     &xReturnedProperty );

                break;
            }

            case eBTpropertyBdaddr:
            {
                /* Assume they want an identify address */
                xReturnedProperty.xLen = B_ADDR_LEN;
                xReturnedProperty.pvVal = GAP_GetDevAddress( (uint8_t)true );

                _xBTCallbacks.pxAdapterPropertiesCb( eBTStatusSuccess,
                                                     1,
                                                     &xReturnedProperty );
                break;
            }

            case eBTpropertyTypeOfDevice:
            {
                BTDeviceType_t xDeviceType = eBTdeviceDevtypeBle;
                xReturnedProperty.pvVal = &xDeviceType;
                xReturnedProperty.xLen = sizeof( xDeviceType );
                _xBTCallbacks.pxAdapterPropertiesCb( eBTStatusSuccess,
                                                     1,
                                                     &xReturnedProperty );
                break;
            }

            case eBTpropertyLocalMTUSize:
            {
                xReturnedProperty.pvVal = &l2capMtuSize;
                xReturnedProperty.xLen = sizeof( l2capMtuSize );
                _xBTCallbacks.pxAdapterPropertiesCb( eBTStatusSuccess,
                                                     1,
                                                     &xReturnedProperty );
                break;
            }

#ifdef GAP_BOND_MGR
            case eBTpropertyBondable:
            {
                uint8_t bBondingEnabled;
                xStackStatus = GAPBondMgr_GetParameter( GAPBOND_BONDING_ENABLED,
                                                        &bBondingEnabled );

                xStatus = _IotBleHalTypes_ConvertStatus( xStackStatus );
                xReturnedProperty.pvVal = &bBondingEnabled;
                xReturnedProperty.xLen = sizeof( bool );
                _xBTCallbacks.pxAdapterPropertiesCb( xStatus,
                                                     1,
                                                     &xReturnedProperty );
                break;
            }

            case eBTpropertyIO:
            {
                uint8_t ucIoCap;
                BTIOtypes_t xIoType;
                xStackStatus = GAPBondMgr_GetParameter( GAPBOND_IO_CAPABILITIES,
                                                        &ucIoCap );

                xStatus = _IotBleHalTypes_ConvertStatus( xStackStatus );

                /* Convert TI BLE-Stack op-codes to AFR */
                switch ( ucIoCap )
                {
                    case GAPBOND_IO_CAP_NO_INPUT_NO_OUTPUT:
                        xIoType = eBTIONone;
                        break;
                    case GAPBOND_IO_CAP_DISPLAY_ONLY:
                        xIoType = eBTIODisplayOnly;
                        break;
                    case GAPBOND_IO_CAP_DISPLAY_YES_NO:
                        xIoType = eBTIODisplayYesNo;
                        break;
                    case GAPBOND_IO_CAP_KEYBOARD_ONLY:
                        xIoType = eBTIOKeyboardOnly;
                        break;

                    default:
                        xIoType = eBTIONone;
                        break;
                }
                xReturnedProperty.pvVal = &xIoType;
                xReturnedProperty.xLen = sizeof( ucIoCap );
                _xBTCallbacks.pxAdapterPropertiesCb( xStatus,
                                                     1,
                                                     &xReturnedProperty );
                break;
            }

            case eBTpropertySecureConnectionOnly:
            {
                uint8_t ucSecureConnectionOnly = false;
                bool bSecureConnOnly = false;
                xStackStatus = GAPBondMgr_GetParameter( GAPBOND_SECURE_CONNECTION,
                                                        &ucSecureConnectionOnly );

                if (ucSecureConnectionOnly == GAPBOND_SECURE_CONNECTION_ONLY)
                {
                    bSecureConnOnly = true;
                }
                xStatus = _IotBleHalTypes_ConvertStatus( xStackStatus );
                xReturnedProperty.pvVal = &bSecureConnOnly;
                xReturnedProperty.xLen = sizeof( bSecureConnOnly );
                _xBTCallbacks.pxAdapterPropertiesCb( xStatus,
                                                     1,
                                                     &xReturnedProperty );
            }
#endif

            case eBTpropertyAdapterBondedDevices:
                /* This requires changes to the bondmgr */
                xStatus = eBTStatusUnsupported;

               break;

            default:
                xStatus = eBTStatusUnsupported;
                _xBTCallbacks.pxAdapterPropertiesCb( eBTStatusFail, 0, NULL );
        }
    }

    return ( xStatus );
}


/*-----------------------------------------------------------*/

static BTStatus_t _prvBTSetDeviceProperty( const BTProperty_t * pxProperty )
{
    BTStatus_t xStatus = eBTStatusSuccess;
    bStatus_t  xStackStatus = SUCCESS;

    switch( pxProperty->xType )
    {
        case eBTpropertyBdname:
        {
            /* The stack can't handle device names longer than
             * GAP_DEVICE_NAME_LEN
             */
            if( pxProperty->xLen > GAP_DEVICE_NAME_LEN )
            {
                return ( eBTStatusParamInvalid );
            }

            /* Set the Device Name characteristic in the GAP GATT Service */
            xStackStatus = GGS_SetParameter( GGS_DEVICE_NAME_ATT,
                                             pxProperty->xLen,
                                             pxProperty->pvVal );

            xStatus = _IotBleHalTypes_ConvertStatus( xStackStatus );

            if( ( _xBTCallbacks.pxAdapterPropertiesCb != NULL ) &&
                ( xStatus == eBTStatusSuccess ) )
            {
                _xBTCallbacks.pxAdapterPropertiesCb( xStatus,
                                                     1,
                                                     ( BTProperty_t * ) pxProperty );
            }

            break;
        }

        case eBTpropertyBdaddr:
        {
            xStatus = eBTStatusUnsupported;
            break;
        }

        case eBTpropertyTypeOfDevice:
        {
            xStatus = eBTStatusUnsupported;
            break;
        }

        case eBTpropertyLocalMTUSize:
        {
            uint16_t usMtuSize = *( ( uint32_t * ) pxProperty->pvVal );

            /* MTU is a 16-bit field, error if user didn't pass the right size */
            if( pxProperty->xLen != sizeof( uint16_t) )
            {
                return ( eBTStatusParamInvalid );
            }

            /* Check that BLE-Stack is built to support the selected MTU */
            if( usMtuSize + L2CAP_HDR_SIZE > MAX_PDU_SIZE )
            {
                return ( eBTStatusParamInvalid );
            }

            /* You can't update MTU while connected */
            /* The empty parameter "" is intentionally added to work around an
             * issue with the icall_directAPI function mapping and GCC compiler
             */
            if ( linkDB_NumActive("") > 0 )
            {
                return ( eBTStatusBusy );
            }

            /* This currently assumes that we're a GATT server
             * It is also a bit of a hack, as it is accessing a stack global
             * variable directly. Do this in a CS to prevent the stack from
             * preempting us
             */
            vPortEnterCritical();
            l2capMtuSize = usMtuSize;
            vPortExitCritical();

            if( ( _xBTCallbacks.pxAdapterPropertiesCb != NULL ) &&
                ( xStatus == eBTStatusSuccess ) )
            {
                _xBTCallbacks.pxAdapterPropertiesCb( xStatus,
                                                     1,
                                                     ( BTProperty_t * ) pxProperty );
            }

            break;
        }

#ifdef GAP_BOND_MGR
        case eBTpropertyBondable:
        {
            xStackStatus =  GAPBondMgr_SetParameter( GAPBOND_BONDING_ENABLED,
                                                     (uint8_t)pxProperty->xLen,
                                                     (uint8_t *)pxProperty->pvVal );

            xStatus = _IotBleHalTypes_ConvertStatus( xStackStatus );

            if( ( _xBTCallbacks.pxAdapterPropertiesCb != NULL ) &&
                ( xStatus == eBTStatusSuccess ) )
            {
                _xBTCallbacks.pxAdapterPropertiesCb( xStatus,
                                                     1,
                                                     ( BTProperty_t * ) pxProperty );
            }

            break;
        }

        case eBTpropertyIO:
        {
            uint8_t ucIoCap = GAPBOND_IO_CAP_NO_INPUT_NO_OUTPUT;
            switch( *( ( BTIOtypes_t * ) pxProperty->pvVal ) )
            {
                case eBTIONone:
                    ucIoCap = GAPBOND_IO_CAP_NO_INPUT_NO_OUTPUT;
                    break;

                case eBTIODisplayOnly:
                    ucIoCap = GAPBOND_IO_CAP_DISPLAY_ONLY;
                    break;

                case eBTIODisplayYesNo:
                    ucIoCap = GAPBOND_IO_CAP_DISPLAY_YES_NO;
                    break;

                case eBTIOKeyboardOnly:
                    ucIoCap = GAPBOND_IO_CAP_KEYBOARD_ONLY;
                    break;

                case eBTIOKeyboardDisplay:
                    ucIoCap = GAPBOND_IO_CAP_KEYBOARD_DISPLAY;
                    break;

                default:
                    break;
            }

            xStackStatus = GAPBondMgr_SetParameter( GAPBOND_IO_CAPABILITIES,
                                                    (uint8_t)pxProperty->xLen,
                                                    &ucIoCap );
            xStatus = _IotBleHalTypes_ConvertStatus( xStackStatus );

            if( ( _xBTCallbacks.pxAdapterPropertiesCb != NULL ) &&
                ( xStatus == eBTStatusSuccess ) )
            {
                _xBTCallbacks.pxAdapterPropertiesCb( xStatus,
                                                     1,
                                                     ( BTProperty_t * ) pxProperty );
            }

            break;
        }

        case eBTpropertySecureConnectionOnly:
        {
            uint8_t ucSecureConnection = GAPBOND_SECURE_CONNECTION_ALLOW;

            if ( *( ( bool * ) pxProperty->pvVal ) )
            {
                ucSecureConnection = GAPBOND_SECURE_CONNECTION_ONLY;
            }

            /* Set Secure Connection Usage during Pairing */
            xStackStatus = GAPBondMgr_SetParameter( GAPBOND_SECURE_CONNECTION,
                                                    sizeof(uint8_t),
                                                    &ucSecureConnection );

            xStatus = _IotBleHalTypes_ConvertStatus( xStackStatus );
            if( ( _xBTCallbacks.pxAdapterPropertiesCb != NULL ) &&
                ( xStatus == eBTStatusSuccess ) )
            {
                _xBTCallbacks.pxAdapterPropertiesCb( xStatus,
                                                     1,
                                                     ( BTProperty_t * ) pxProperty );
            }

            break;
        }
#endif

        default:
            xStatus = eBTStatusUnsupported;
    }

    return ( xStatus );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTGetAllRemoteDeviceProperties( BTBdaddr_t * pxRemoteAddr )
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTGetRemoteDeviceProperty( BTBdaddr_t * pxRemoteAddr,
                                                 BTPropertyType_t type )
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTSetRemoteDeviceProperty( BTBdaddr_t * pxRemoteAddr,
                                                 const BTProperty_t * property )
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTPair( const BTBdaddr_t * pxBdAddr,
                              BTTransport_t xTransport,
                              bool bCreateBond )
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTCreateBondOutOfBand( const BTBdaddr_t * pxBdAddr,
                                             BTTransport_t xTransport,
                                             const BTOutOfBandData_t * pxOobData )
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTCancelBond( const BTBdaddr_t * pxBdAddr )
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTRemoveBond( const BTBdaddr_t * pxBdAddr )
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTGetConnectionState( const BTBdaddr_t * pxBdAddr,
                                            bool * bConnectionState )
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTPinReply( const BTBdaddr_t * pxBdAddr,
                                  uint8_t ucAccept,
                                  uint8_t ucPinLen,
                                  BTPinCode_t * pxPinCode )
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTSspReply( const BTBdaddr_t * pxBdAddr,
                                  BTSspVariant_t xVariant,
                                  uint8_t ucAccept,
                                  uint32_t ulPasskey )
{

    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTReadEnergyInfo()
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTDutModeConfigure( bool bEnable )
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTDutModeSend( uint16_t usOpcode,
                                     uint8_t * pucBuf,
                                     size_t xLen )
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTLeTestMode( uint16_t usOpcode,
                                    uint8_t * pucBuf,
                                    size_t xLen )
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTConfigHCISnoopLog( bool bEnable )
{
    return ( eBTStatusUnsupported );
}


/*-----------------------------------------------------------*/

static BTStatus_t _prvBTConfigClear()
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTReadRssi( const BTBdaddr_t * pxBdAddr )
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static BTStatus_t _prvBTGetTxpower( const BTBdaddr_t * pxBdAddr,
                                    BTTransport_t xTransport )
{
    return ( eBTStatusUnsupported );
}

/*-----------------------------------------------------------*/

static void _prvAssertHandler( uint8_t ucAssertCause, uint8_t ucAssertSubcause )
{
  HAL_ASSERT_SPINLOCK;
  return;
}

/*-----------------------------------------------------------*/

static const void * _prvGetClassicAdapter()
{
    return ( NULL );
}

/*-----------------------------------------------------------*/

const BTInterface_t * BTGetBluetoothInterface()
{
    return ( &xBTinterface );
}

/*-----------------------------------------------------------*/
