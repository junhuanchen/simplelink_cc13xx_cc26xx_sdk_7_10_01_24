/*
 * Copyright 2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 *
 * AMAZON PROPRIETARY/CONFIDENTIAL
 *
 * You may not use this file except in compliance with the terms and
 * conditions set forth in the accompanying LICENSE.TXT file. This file is a
 * Modifiable File, as defined in the accompanying LICENSE.TXT file.
 *
 * THESE MATERIALS ARE PROVIDED ON AN "AS IS" BASIS. AMAZON SPECIFICALLY
 * DISCLAIMS, WITH RESPECT TO THESE MATERIALS, ALL WARRANTIES, EXPRESS,
 * IMPLIED, OR STATUTORY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
 */


/*-------------------------------------\
|                                      |
| this file is automatically generated |
|            do not modify             |
|                                      |
\_____________________________________*/

#ifndef _ACE_MAIN_H_
#define _ACE_MAIN_H_

#include <ace/ace.h>

/* Initializes and starts the ACE modules (if autostart is enabled) */
void ace_main(void);

/*
 * Initializes and starts the ACE modules with the provided user config
 * (if autostart is enabled).
 * Refer ace_user_config.h to see the definition of the structure.
 */
void ace_mainWithConfig(aceUserConfig_config_t* ace_config);

#endif /* _ACE_MAIN_H_ */
