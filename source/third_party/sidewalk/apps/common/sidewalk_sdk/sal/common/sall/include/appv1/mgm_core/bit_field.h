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

#ifndef RNETC_INCLUDE_APPV1_MGM_CORE_BIT_FIELD_H_
#define RNETC_INCLUDE_APPV1_MGM_CORE_BIT_FIELD_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    HALO_HALL_APPV1_VERSION_MAJOR_MASK = 0xf,
    HALO_HALL_APPV1_VERSION_MAJOR_OFFSET = 4,
    HALO_HALL_APPV1_VERSION_MINOR_MASK = 0xf,
    HALO_HALL_APPV1_VERSION_MINOR_OFFSET = 0,
} halo_hall_appv1_security_field;

typedef enum {
    HALO_HALL_APPV1_GCS_UNCERTAINTY_UNITS_MASK = 0x3,
    HALO_HALL_APPV1_GCS_UNCERTAINTY_UNITS_OFFSET = 6,

    HALO_HALL_APPV1_GCS_UNCERTAINTY_MASK = 0x3F,
    HALO_HALL_APPV1_GCS_UNCERTAINTY_DYTE_MASK = 0xFF,

    HALO_HALL_APPV1_GCS_UNCERTAINTY_OFFSET = 8
} halo_hall_appv1_gcs_uncertainty_field;

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* RNETC_INCLUDE_APPV1_MGM_CORE_BIT_FIELD_H_ */