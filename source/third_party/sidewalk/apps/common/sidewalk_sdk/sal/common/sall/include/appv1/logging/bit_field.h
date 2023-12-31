/*
 * Copyright 2019-2021 Amazon.com, Inc. or its affiliates. All rights reserved.
 *
 * AMAZON PROPRIETARY/CONFIDENTIAL
 *
 * You may not use this file except in compliance with the terms and
 * conditions set forth in the accompanying LICENSE.TXT file.
 *
 * THESE MATERIALS ARE PROVIDED ON AN "AS IS" BASIS. AMAZON SPECIFICALLY
 * DISCLAIMS, WITH RESPECT TO THESE MATERIALS, ALL WARRANTIES, EXPRESS,
 * IMPLIED, OR STATUTORY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
 */

#ifndef HALO_ALL_APPV1_LOGGING_BIT_FIELD_H_
#define HALO_ALL_APPV1_LOGGING_BIT_FIELD_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    HALO_ALL_LOGGING_RF_MODE_MASK = 0x7,
    HALO_ALL_LOGGING_RF_MODE_OFFSET = 5,
    HALO_ALL_LOGGING_LOG_CFG_MASK = 0x3,
    HALO_ALL_LOGGING_LOG_CFG_OFFSET = 3,
    HALO_ALL_LOGGING_LOG_LINK_MASK = 0x3,
    HALO_ALL_LOGGING_LOG_LINK_OFFSET = 1,
    HALO_ALL_LOGGING_ENABLE_MASK = 0x1,
    HALO_ALL_LOGGING_ENABLE_OFFSET = 0,
    HALO_ALL_LOGGING_LOG_LEVEL_MASK = 0xF,
    HALO_ALL_LOGGING_LOG_LEVEL_OFFSET = 12,
    HALO_ALL_LOGGING_LOG_ID_MASK = 0xFFF,
    HALO_ALL_LOGGING_LOG_ID_OFFSET = 0,
    HALO_ALL_LOGGING_LOG_CFG_ML_MASK = 0x3,
    HALO_ALL_LOGGING_LOG_CFG_ML_OFFSET = 0,
    HALO_ALL_LOGGING_LOG_LEVEL_ML_MASK = 0xF,
    HALO_ALL_LOGGING_LOG_LEVEL_ML_OFFSET = 2,

} halo_all_logging_helps;

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* HALO_ALL_APPV1_LOGGING_BIT_FIELD_H_ */
