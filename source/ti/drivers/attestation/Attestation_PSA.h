/*
 * Copyright (c) 2022-2023, Texas Instruments Incorporated
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
/** ============================================================================
 *  @file       Attestation_PSA.h
 *
 *  @brief      Attestation driver header
 *
 * # Overview #
 * This file contains the APIs to generate an attestation token and obtain the
 * expected token size to create a buffer to store the generated token.
 * Attestation_PSA APIs are only available when TF-M is enabled and this file provides
 * the non-secure interface to the Attestation_PSA driver.
 *
 * # Usage #
 *
 * After calling the Attestation initialization function, a token can be generated
 * using the challenge provided by the attestation service to Attestation_PSA API.
 * To generate a token, Attestation_PSA APIs assume that attestation keys are
 * pre-provisioned in the pre-provisioned key sector.
 *
 * @anchor ti_drivers_attestation_Attestation_PSA_Example
 *
 * ## Generating an attestation token #
 *
 * @code
 *
 * #include <ti/drivers/attestation/Attestation_PSA.h>
 * ....
 *
 * // Initialize Attestation_PSA driver
 * Attestation_PSA_init();
 *
 * // A buffer of maximum allowed token size to store the generated token
 * // Alternatively, application can obtain the size of token using Attestation_PSA_getTokenSize()
 * // to dynamically allocate buffer of required size
 * uint8_t token[ATTESTATION_PSA_MAX_TOKEN_SIZE];
 *
 * // A buffer for nonce or challenge provided by the attestation service to prevent replay or re-use of token
 * uint8_t nonce[32];
 *
 * int_fast16_t status;
 * size_t tokenLength;
 *
 * // Generate the token
 * status = Attestation_PSA_getToken(&nonce[0], sizeof(nonce), &token[0], sizeof(token), &tokenLength);
 *
 * if (status != ATTESTATION_PSA_STATUS_SUCCESS)
 * {
 *      // Handle error
 * }
 * @endcode
 *
 */

#ifndef ti_drivers_attestation_Attestation_PSA__include
#define ti_drivers_attestation_Attestation_PSA__include

#include <stdint.h>
#include <stddef.h>

#include <psa/initial_attestation.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Maximum attestation token size
 *
 * The maximum size of an attestation token that can be generated by the
 * attestation service. Used to configure buffers for services that verify the
 * produced tokens.
 */
#define ATTESTATION_PSA_MAX_TOKEN_SIZE (PSA_INITIAL_ATTEST_MAX_TOKEN_SIZE)

/*!
 * @brief   Successful status code.
 *
 * Functions return ATTESTATION_PSA_STATUS_SUCCESS if the function was executed
 * successfully.
 */
#define ATTESTATION_PSA_STATUS_SUCCESS ((int_fast16_t)0)

/*!
 * @brief   Generic error status code.
 *
 * Functions return ATTESTATION_PSA_STATUS_ERROR if the function was not executed
 * successfully and no more pertinent error code could be returned.
 */
#define ATTESTATION_PSA_STATUS_ERROR ((int_fast16_t)-1)

/*!
 * @brief   An error status code returned if the hardware or software resource
 * is currently unavailable.
 *
 * Attestation driver implementations may have hardware or software limitations on how
 * many clients can simultaneously perform operations. This status code is returned
 * if the mutual exclusion mechanism signals that an operation cannot currently be performed.
 */
#define ATTESTATION_PSA_STATUS_RESOURCE_UNAVAILABLE ((int_fast16_t)-2)

/*!
 * @brief   Operation failed due to invalid inputs.
 *
 * Functions return ATTESTATION_PSA_STATUS_INVALID_INPUTS if input validation fails.
 */
#define ATTESTATION_PSA_STATUS_INVALID_INPUTS ((int_fast16_t)-3)

/**
 *  @brief Get initial attestation token
 *
 *  @param[in]     auth_challenge  Pointer to buffer where challenge input is
 *                                 stored.
 *  @param[in]     challenge_size  Size of challenge object in bytes.
 *                                 Must be 32, 48, or 64-bytes.
 *  @param[out]    token_buf       Pointer to the buffer where attestation token
 *                                 will be stored, with a maximum buffer size
 *                                 of ATTESTATION_PSA_MAX_TOKEN_SIZE.
 *  @param[in]     token_buf_size  Size of allocated buffer for token, in bytes.
 *  @param[out]    token_size      Size of the token that has been returned, in
 *                                 bytes.
 *
 *  @retval #ATTESTATION_PSA_STATUS_SUCCESS                 The operation succeeded.
 *  @retval #ATTESTATION_PSA_STATUS_ERROR                   The operation failed.
 *  @retval #ATTESTATION_PSA_STATUS_RESOURCE_UNAVAILABLE    The required hardware resource was not available.
 *                                                          Try again later.
 *  @retval #ATTESTATION_PSA_STATUS_INVALID_INPUTS          Input validation failed.
 */
int_fast16_t Attestation_PSA_getToken(const uint8_t *auth_challenge,
                                      size_t challenge_size,
                                      uint8_t *token_buf,
                                      size_t token_buf_size,
                                      size_t *token_size);

/**
 *  @brief Get the exact size of initial attestation token in bytes.
 *
 *  Returns the size of the IAT token. It can be used if the caller
 *  dynamically allocates memory for the token buffer.
 *
 *  @param[in]   challenge_size  Size of challenge object in bytes.
 *                               Must be 32, 48, or 64-bytes.
 *  @param[out]  token_size      Size of the token in bytes, which is created by
 *                               initial attestation service.
 *
 *  @retval #ATTESTATION_PSA_STATUS_SUCCESS                 The operation succeeded.
 *  @retval #ATTESTATION_PSA_STATUS_ERROR                   The operation failed.
 *  @retval #ATTESTATION_PSA_STATUS_RESOURCE_UNAVAILABLE    The required hardware resource was not available.
 *                                                          Try again later.
 *  @retval #ATTESTATION_PSA_STATUS_INVALID_INPUTS          Input validation failed.
 */
int_fast16_t Attestation_PSA_getTokenSize(size_t challenge_size, size_t *token_size);

/*!
 *  @brief  This function initializes the Attestation module.
 *
 *  @pre    This function must also be called before
 *          any other Attestation driver APIs. This function call does not modify any
 *          peripheral registers.
 */
void Attestation_PSA_init(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_attestation_Attestation_PSA__include */
