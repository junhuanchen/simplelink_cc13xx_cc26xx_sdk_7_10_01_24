/*
 * Copyright 2020-2021 Amazon.com, Inc. or its affiliates. All rights reserved.
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

/* Tag definitions: 1~255 */
#define HALO_EVENT_LOG_TAG_RESERVED   0
#define HALO_EVENT_LOG_TAG_BOOTLOADER 1

/* Tag Reserved */
#define HALO_EVENT_LOG_MODULE_RESERVED_TEST 0
HALO_EVENT_LOG_DEFINE(HALO_EVENT_LOG_ID(RESERVED, TEST, 0), EVENT_LOG_FIRST_EVENT,  "This is the first event, I have arg=%d %d %d!!")
HALO_EVENT_LOG_DEFINE(HALO_EVENT_LOG_ID(RESERVED, TEST, 1), EVENT_LOG_SECOND_EVENT, "This is the second event!!")


/* Tag for Bootloader */
#define HALO_EVENT_LOG_MODULE_BOOTLOADER_INIT 0
#define HALO_EVENT_LOG_MODULE_BOOTLOADER_DFU  1
HALO_EVENT_LOG_DEFINE(HALO_EVENT_LOG_ID(BOOTLOADER, INIT, 0), EVENT_LOG_BOOTLOADER_START,    "Bootloader starts")
HALO_EVENT_LOG_DEFINE(HALO_EVENT_LOG_ID(BOOTLOADER, DFU,  0), EVENT_LOG_BOOTLOADER_GOTO_DFU, "Bootloader is entring DFU mode")
