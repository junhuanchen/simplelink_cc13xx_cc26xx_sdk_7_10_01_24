/*
 * Copyright (c) 2018-2020, Arm Limited. All rights reserved.
 * Copyright (c) 2022, Texas Instruments Incorporated. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <inttypes.h>
#include <stdio.h>
#include "tfm/tfm_core_svc.h"
#include "psa/client.h"
#include "psa/service.h"

__attribute__((naked))
psa_signal_t psa_wait(psa_signal_t signal_mask, uint32_t timeout)

{
    __ASM volatile("SVC %0           \n"
                   "BX LR            \n"
                   : : "I" (TFM_SVC_PSA_WAIT));
}

__attribute__((naked))
psa_status_t psa_get(psa_signal_t signal, psa_msg_t *msg)
{
    __ASM volatile("SVC %0           \n"
                   "BX LR            \n"
                   : : "I" (TFM_SVC_PSA_GET));
}

__attribute__((naked))
void psa_set_rhandle(psa_handle_t msg_handle, void *rhandle)
{
    __ASM volatile("SVC %0           \n"
                   "BX LR            \n"
                   : : "I" (TFM_SVC_PSA_SET_RHANDLE));
}

__attribute__((naked))
size_t psa_read(psa_handle_t msg_handle, uint32_t invec_idx,
                void *buffer, size_t num_bytes)

{
    __ASM volatile("SVC %0           \n"
                   "BX LR            \n"
                   : : "I" (TFM_SVC_PSA_READ));
}

__attribute__((naked))
size_t psa_skip(psa_handle_t msg_handle, uint32_t invec_idx, size_t num_bytes)
{
    __ASM volatile("SVC %0           \n"
                   "BX LR            \n"
                   : : "I" (TFM_SVC_PSA_SKIP));
}

__attribute__((naked))
void psa_write(psa_handle_t msg_handle, uint32_t outvec_idx,
               const void *buffer, size_t num_bytes)
{
    __ASM volatile("SVC %0           \n"
                   "BX LR            \n"
                   : : "I" (TFM_SVC_PSA_WRITE));
}

__attribute__((naked))
void psa_reply(psa_handle_t msg_handle, psa_status_t retval)
{
    __ASM volatile("SVC %0           \n"
                   "BX LR            \n"
                   : : "I" (TFM_SVC_PSA_REPLY));
}

__attribute__((naked))
void psa_notify(int32_t partition_id)
{
    __ASM volatile("SVC %0           \n"
                   "BX LR            \n"
                   : : "I" (TFM_SVC_PSA_NOTIFY));
}

__attribute__((naked))
void psa_clear(void)
{
    __ASM volatile("SVC %0           \n"
                   "BX LR            \n"
                   : : "I" (TFM_SVC_PSA_CLEAR));
}

__attribute__((naked))
void psa_eoi(psa_signal_t irq_signal)
{
    __ASM volatile("SVC %0           \n"
                   "BX LR            \n"
                   : : "I" (TFM_SVC_PSA_EOI));
}

/* [TI-TFM] Added psa_eoi_no_irq_en to support level-triggered interrupt */
__attribute__((naked))
void psa_eoi_no_irq_en(psa_signal_t irq_signal)
{
    __ASM volatile("SVC %0           \n"
                   "BX LR            \n"
                   : : "I" (TFM_SVC_PSA_EOI_NO_IRQ_EN));
}

__attribute__((naked))
void psa_panic(void)
{
    __ASM volatile("SVC %0           \n"
                   "BX LR            \n"
                   : : "I" (TFM_SVC_PSA_PANIC));
}
