#-------------------------------------------------------------------------------
# Copyright (c) 2018-2020, Arm Limited. All rights reserved.
# Copyright (c) 2019-2022, Texas Instruments Incorporated. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#
#-------------------------------------------------------------------------------

#This file holds information of a specific build configuration of this project.

if(NOT DEFINED TFM_ROOT_DIR)
	message(FATAL_ERROR "Variable TFM_ROOT_DIR is not set!")
endif()

#Include board specific config (CPU, etc...), select platform specific build
#system settings file
if(NOT DEFINED TARGET_PLATFORM)
	message(FATAL_ERROR "ERROR: TARGET_PLATFORM is not set in command line")
elseif(${TARGET_PLATFORM} STREQUAL "AN521")
	set(PLATFORM_CMAKE_FILE "${TFM_ROOT_DIR}/platform/ext/Mps2AN521.cmake")
elseif(${TARGET_PLATFORM} STREQUAL "AN519")
	set(PLATFORM_CMAKE_FILE "${TFM_ROOT_DIR}/platform/ext/Mps2AN519.cmake")
elseif(${TARGET_PLATFORM} STREQUAL "AN539")
	set(PLATFORM_CMAKE_FILE "${TFM_ROOT_DIR}/platform/ext/Mps2AN539.cmake")
elseif(${TARGET_PLATFORM} STREQUAL "FVP_SSE300_MPS2")
	set(PLATFORM_CMAKE_FILE "${TFM_ROOT_DIR}/platform/ext/fvp_sse300_mps2.cmake")
elseif(${TARGET_PLATFORM} STREQUAL "AN524")
	set(PLATFORM_CMAKE_FILE "${TFM_ROOT_DIR}/platform/ext/Mps3AN524.cmake")
elseif(${TARGET_PLATFORM} STREQUAL "LPC55S69")
	set(PLATFORM_CMAKE_FILE "${TFM_ROOT_DIR}/platform/ext/lpc55s69.cmake")
elseif(${TARGET_PLATFORM} STREQUAL "MUSCA_A")
	set(PLATFORM_CMAKE_FILE "${TFM_ROOT_DIR}/platform/ext/musca_a.cmake")
elseif(${TARGET_PLATFORM} STREQUAL "MUSCA_B1")
	set(PLATFORM_CMAKE_FILE "${TFM_ROOT_DIR}/platform/ext/musca_b1.cmake")
elseif(${TARGET_PLATFORM} STREQUAL "MUSCA_S1")
	set(PLATFORM_CMAKE_FILE "${TFM_ROOT_DIR}/platform/ext/musca_s1.cmake")
elseif(${TARGET_PLATFORM} STREQUAL "psoc64")
	set(PLATFORM_CMAKE_FILE "${TFM_ROOT_DIR}/platform/ext/psoc64.cmake")
elseif(${TARGET_PLATFORM} STREQUAL "SSE-200_AWS")
	set(PLATFORM_CMAKE_FILE "${TFM_ROOT_DIR}/platform/ext/SSE-200_AWS.cmake")
elseif(${TARGET_PLATFORM} MATCHES "^STM")
	set(PLATFORM_CMAKE_FILE "${TFM_ROOT_DIR}/platform/ext/stm.cmake")
#[TI-TFM] CC26x4 support
elseif(${TARGET_PLATFORM} STREQUAL "CC26X4")
	set(PLATFORM_CMAKE_FILE "${TFM_ROOT_DIR}/platform/ext/cc26x4.cmake")
	set(TI_TFM True)
else()
	message(FATAL_ERROR "ERROR: Target \"${TARGET_PLATFORM}\" is not supported.")
endif()

# Select IPC model
set (CORE_IPC True)

##These variables select how the projects are built. Each project will set
#various project specific settings (e.g. what files to build, macro
#definitions) based on these.
set (REGRESSION False)
set (CORE_TEST False)
set (IPC_TEST False)
set (PSA_API_TEST False)

# TF-M isolation level: 1, 2
set (TFM_LVL 1)

include ("${TFM_ROOT_DIR}/CommonConfig.cmake")
