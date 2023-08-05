/*
 * Copyright (c) 2022 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ti_drivers_aesgcm_AESGCMCC26X4_s__include
#define ti_drivers_aesgcm_AESGCMCC26X4_s__include

#include <stdint.h>

#include <ti/drivers/crypto/CryptoCC26X4_s.h>
#include <ti/drivers/AESGCM.h>

#include <ti/drivers/tfm/SecureCallback.h>

#include <third_party/tfm/interface/include/psa/error.h>
#include <third_party/tfm/interface/include/psa/service.h>

#if defined(TFM_PSA_API)
    #include "ti_drivers_config.h" /* Sysconfig generated header */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * AES GCM secure message types
 *
 * Non-secure clients must register their callback after opening or
 * constructing a driver instance with blocking or callback return behavior.
 */
#define AESGCM_S_MSG_TYPE_CONSTRUCT (CRYPTO_S_MSG_TYPE_INDEX_AESGCM | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + 0U)))
#define AESGCM_S_MSG_TYPE_OPEN      (CRYPTO_S_MSG_TYPE_INDEX_AESGCM | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + 1U)))
#define AESGCM_S_MSG_TYPE_REGISTER_CALLBACK \
    (CRYPTO_S_MSG_TYPE_INDEX_AESGCM | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + 2U)))
#define AESGCM_S_MSG_TYPE_CLOSE (CRYPTO_S_MSG_TYPE_INDEX_AESGCM | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + 3U)))
#define AESGCM_S_MSG_TYPE_ONE_STEP_ENCRYPT \
    (CRYPTO_S_MSG_TYPE_INDEX_AESGCM | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + 4U)))
#define AESGCM_S_MSG_TYPE_ONE_STEP_DECRYPT \
    (CRYPTO_S_MSG_TYPE_INDEX_AESGCM | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + 5U)))
#define AESGCM_S_MSG_TYPE_SETUP_ENCRYPT \
    (CRYPTO_S_MSG_TYPE_INDEX_AESGCM | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + 6U)))
#define AESGCM_S_MSG_TYPE_SETUP_DECRYPT \
    (CRYPTO_S_MSG_TYPE_INDEX_AESGCM | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + 7U)))
#define AESGCM_S_MSG_TYPE_SET_LENGTHS (CRYPTO_S_MSG_TYPE_INDEX_AESGCM | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + 8U)))
#define AESGCM_S_MSG_TYPE_SET_IV      (CRYPTO_S_MSG_TYPE_INDEX_AESGCM | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + 9U)))
#define AESGCM_S_MSG_TYPE_ADD_AAD     (CRYPTO_S_MSG_TYPE_INDEX_AESGCM | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + 10U)))
#define AESGCM_S_MSG_TYPE_ADD_DATA    (CRYPTO_S_MSG_TYPE_INDEX_AESGCM | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + 11U)))
#define AESGCM_S_MSG_TYPE_FINALIZE_ENCRYPT \
    (CRYPTO_S_MSG_TYPE_INDEX_AESGCM | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + 12U)))
#define AESGCM_S_MSG_TYPE_FINALIZE_DECRYPT \
    (CRYPTO_S_MSG_TYPE_INDEX_AESGCM | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + 13U)))
#define AESGCM_S_MSG_TYPE_CANCEL_OPERATION \
    (CRYPTO_S_MSG_TYPE_INDEX_AESGCM | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + 14U)))

/*
 * Config pool size determines how many dynamic driver instances can be created
 * by the non-secure client using AESGCM_construct().
 */
#ifndef CONFIG_AESGCM_S_CONFIG_POOL_SIZE
    #define CONFIG_AESGCM_S_CONFIG_POOL_SIZE 1
#endif

#define AESGCM_SECURE_CALLBACK_COUNT (CONFIG_TI_DRIVERS_AESGCM_COUNT + CONFIG_AESGCM_S_CONFIG_POOL_SIZE)

/*
 * ========= AES GCM Secure Callback struct =========
 */
typedef struct
{
    SecureCallback_Object object;
    /* AES GCM callback fxn parameters */
    AESGCM_Handle handle;
    int_fast16_t returnValue;
    AESGCM_OperationUnion *operation;
    AESGCM_OperationType operationType;
} AESGCM_s_SecureCallback;

/*
 * ========= AES GCM Secure Message Structs =========
 * These secure message structs correspond to the secure message types defined
 * above. Together, they are used by non-secure client to make PSA calls to the
 * AES GCM secure service. There is a single input vector for the PSA call
 * which is a pointer to secure message struct. If the underlying function
 * has a return value, there is a single output vector which is a pointer to
 * storage for the return value.
 */
typedef struct
{
    AESGCM_Config *config;
    const AESGCM_Params *params;
} AESGCM_s_ConstructMsg;

typedef struct
{
    uint_least8_t index;
    const AESGCM_Params *params;
} AESGCM_s_OpenMsg;

typedef struct
{
    AESGCM_Handle handle;
    AESGCM_s_SecureCallback *callback;
} AESGCM_s_CallbackMsg;

typedef struct
{
    AESGCM_Handle handle;
} AESGCM_s_CloseMsg;

typedef struct
{
    AESGCM_Handle handle;
    AESGCM_OneStepOperation *operation;
} AESGCM_s_OneStepOperationMsg;

typedef struct
{
    AESGCM_Handle handle;
    const CryptoKey *key;
    size_t totalAADLength;
    size_t totalPlaintextLength;
} AESGCM_s_SetupOperationMsg;

typedef struct
{
    AESGCM_Handle handle;
    size_t aadLength;
    size_t plaintextLength;
} AESGCM_s_SetLengthsMsg;

typedef struct
{
    AESGCM_Handle handle;
    const uint8_t *iv;
    size_t ivLength;
} AESGCM_s_SetIVMsg;

typedef struct
{
    AESGCM_Handle handle;
    AESGCM_SegmentedAADOperation *operation;
} AESGCM_s_AddAADMsg;

typedef struct
{
    AESGCM_Handle handle;
    AESGCM_SegmentedDataOperation *operation;
} AESGCM_s_AddDataMsg;

typedef struct
{
    AESGCM_Handle handle;
    AESGCM_SegmentedFinalizeOperation *operation;
} AESGCM_s_FinalizeOperationMsg;

typedef struct
{
    AESGCM_Handle handle;
} AESGCM_s_CancelOperationMsg;

/*!
 *  @brief  Handles PSA messages for AES GCM secure driver
 *
 *  @note   This function should be called by secure partition thread only.
 *
 *  @param [in]  msg     pointer to PSA message
 *
 *  @retval PSA_SUCCESS if successful.
 *  @retval PSA_ERROR_PROGRAMMER_ERROR if any args point to secure addresses.
 */
psa_status_t AESGCM_s_handlePsaMsg(psa_msg_t *msg);

/*!
 *  @brief  Initializes the AES GCM secure driver.
 *
 *  @note   This function should be called by secure partition thread only.
 */
void AESGCM_s_init(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_aesgcm_AESGCMCC26X4_s__include */
