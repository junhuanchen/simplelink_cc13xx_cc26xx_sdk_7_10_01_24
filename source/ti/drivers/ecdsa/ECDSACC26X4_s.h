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

#ifndef ti_drivers_ecdsa_ECDSACC26X4_s__include
#define ti_drivers_ecdsa_ECDSACC26X4_s__include

#include <stdint.h>

#include <ti/drivers/crypto/CryptoCC26X4_s.h>
#include <ti/drivers/ECDSA.h>

#include <ti/drivers/tfm/SecureCallback.h>

#include <third_party/tfm/interface/include/psa/error.h>
#include <third_party/tfm/interface/include/psa/service.h>

#if defined(TFM_PSA_API)
    #include "ti_drivers_config.h" /* Sysconfig generated header */
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define ECDSA_S_MSG_TYPE(index) (CRYPTO_S_MSG_TYPE_INDEX_ECDSA | ((int32_t)1 << (CRYPTO_S_MSG_TYPE_SHIFT + (index))))

/*
 * ECDSA secure message types
 * These secure message structs correspond to the secure message types defined
 * above. Together, they are used by non-secure client to make PSA calls to the
 * ECDSA secure service. There is a single input vector for the PSA call
 * which is a pointer to secure message struct. If the underlying function
 * has a return value, there is a single output vector which is a pointer to
 * storage for the return value.
 */
#define ECDSA_S_MSG_TYPE_CONSTRUCT         ECDSA_S_MSG_TYPE(0U)
#define ECDSA_S_MSG_TYPE_OPEN              ECDSA_S_MSG_TYPE(1U)
#define ECDSA_S_MSG_TYPE_REGISTER_CALLBACK ECDSA_S_MSG_TYPE(2U)
#define ECDSA_S_MSG_TYPE_CLOSE             ECDSA_S_MSG_TYPE(3U)
#define ECDSA_S_MSG_TYPE_SIGN              ECDSA_S_MSG_TYPE(4U)
#define ECDSA_S_MSG_TYPE_VERIFY            ECDSA_S_MSG_TYPE(5U)
#define ECDSA_S_MSG_TYPE_CANCEL_OPERATION  ECDSA_S_MSG_TYPE(6U)

/*
 * Config pool size determines how many dynamic driver instances can be created
 * by the non-secure client using ECDSA_construct().
 */
#ifndef CONFIG_ECDSA_S_CONFIG_POOL_SIZE
    #define CONFIG_ECDSA_S_CONFIG_POOL_SIZE 1
#endif

#define ECDSA_SECURE_CALLBACK_COUNT (CONFIG_TI_DRIVERS_ECDSA_COUNT + CONFIG_ECDSA_S_CONFIG_POOL_SIZE)

/*
 * ========= ECDSA Secure Callback struct =========
 * Non-secure clients must register their callback after opening or
 * constructing a driver instance with blocking or callback return behavior.
 */
typedef struct
{
    SecureCallback_Object object;
    /* ECDSA callback fxn parameters */
    ECDSA_Handle handle;
    int_fast16_t returnStatus;
    ECDSA_Operation operation;
    ECDSA_OperationType operationType;
} ECDSA_s_SecureCallback;

/*
 * ========= ECDSA Secure Message Structs =========
 * These secure message structs correspond to the secure message types defined
 * above. Together, they are used by non-secure client to make PSA calls to the
 * ECDSA secure service. There is a single input vector for the PSA call
 * which is a pointer to secure message struct. If the underlying function
 * has a return value, there is a single output vector which is a pointer to
 * storage for the return value.
 */
typedef struct
{
    ECDSA_Config *config;
    const ECDSA_Params *params;
} ECDSA_s_ConstructMsg;

typedef struct
{
    uint_least8_t index;
    const ECDSA_Params *params;
} ECDSA_s_OpenMsg;

typedef struct
{
    ECDSA_Handle handle;
    ECDSA_s_SecureCallback *callback;
} ECDSA_s_CallbackMsg;

typedef struct
{
    ECDSA_Handle handle;
} ECDSA_s_CloseMsg;

typedef struct
{
    ECDSA_Handle handle;
    ECDSA_OperationSign *operation;
} ECDSA_s_SignMsg;

typedef struct
{
    ECDSA_Handle handle;
    ECDSA_OperationVerify *operation;
} ECDSA_s_VerifyMsg;

typedef struct
{
    ECDSA_Handle handle;
} ECDSA_s_CancelOperationMsg;

/*!
 *  @brief  Handles PSA messages for ECDSA secure driver
 *
 *  @note   This function should be called by secure partition thread only.
 *
 *  @param [in]  msg     pointer to PSA message
 *
 *  @retval PSA_SUCCESS if successful.
 *  @retval PSA_ERROR_PROGRAMMER_ERROR if any args point to secure addresses.
 */
psa_status_t ECDSA_s_handlePsaMsg(psa_msg_t *msg);

/*!
 *  @brief  Initializes the ECDSA secure driver.
 *
 *  @note   This function should be called by secure partition thread only.
 */
void ECDSA_s_init(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_ecdsa_ECDSACC26X4_s__include */
