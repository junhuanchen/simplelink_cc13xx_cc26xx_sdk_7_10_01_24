COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR ?= $(abspath ../../../../../../..)

include $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/imports.mak

CC = "$(TICLANG_ARMCOMPILER)/bin/tiarmclang"
LNK = "$(TICLANG_ARMCOMPILER)/bin/tiarmclang"

SYSCFG_CMD_STUB = $(SYSCONFIG_TOOL) --compiler ticlang --product $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/.metadata/product.json
SYSCFG_FILES := $(shell $(SYSCFG_CMD_STUB) --listGeneratedFiles --listReferencedFiles --output . ../../freertos/sensor.syscfg)

SYSCFG_C_FILES = $(filter %.c,$(SYSCFG_FILES))
SYSCFG_H_FILES = $(filter %.h,$(SYSCFG_FILES))

OBJECTS = application_main.obj application_sensor_sensor.obj application_sensor_ssf.obj application_sensor_link_controller_jdllc.obj software_stack_ti15_4stack_mac_mac_settings_mac_user_config.obj application_cui_cui.obj application_sensor_sm_sm_ti154.obj application_sensor_sm_sm_ecc_ti154.obj application_sensor_sm_sm_toolbox.obj software_stack_ti15_4stack_nv_crc.obj software_stack_ti15_4stack_nv_nvocmp.obj software_stack_ti15_4stack_mac_low_level_mac_activity.obj software_stack_ti15_4stack_mac_mac_settings_mac_cfg.obj software_stack_ti15_4stack_mac_mac_settings_mac_settings.obj software_stack_ti15_4stack_mac_macTask.obj software_stack_ti15_4stack_mac_api_mac.obj $(patsubst %.c,%.obj,$(notdir $(SYSCFG_C_FILES)))
NAME = sensor_sm

CFLAGS = -I../.. \
    -I. \
    @${PROJECT_LOC}/application/defines/sensor.opts \
      \
    -I${PROJECT_ROOT}/application/sensor \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/common/osal_port \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/low_level/cc13xx \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/apps/sensor \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/common/nv \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/common/cui \
    -Oz \
    -std=gnu9x \
    -munaligned-access \
    -fshort-enums \
    -fcommon \
    -funsigned-char \
    -mlittle-endian \
    -fdiagnostics-show-option \
    -ffunction-sections \
    -fno-strict-aliasing \
    -g \
    -DxTIMAC_ROM_IMAGE_BUILD \
    -I${PROJECT_ROOT} \
    -I${PROJECT_ROOT}/application \
    -I${PROJECT_ROOT}/software_stack/ti15_4stack/osal \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/apps \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/common \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/common/boards \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/common/util \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/common/inc \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/common/stack/src \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/common/stack/tirtos/inc \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/common/heapmgr \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/services/saddr \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/services/sdata \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/hal/crypto \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/hal/platform \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/hal/rf \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/fh \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/high_level \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/inc \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/rom \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/inc/cc13xx \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/tracer \
    -DBoard_EXCLUDE_NVS_EXTERNAL_FLASH \
    -DDeviceFamily_CC13X4 \
    "-I$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source" \
    "-I$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/devices/cc13x4_cc26x4" \
    "-I$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/devices/cc13x4_cc26x4/inc" \
    "-I$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/devices/cc13x4_cc26x4/driverlib" \
    "-I$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/third_party/mbedcrypto/ti" \
    "-I$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/third_party/mbedcrypto/include" \
    -DFREERTOS_SUPPORT \
    -DFREERTOS \
    "-I$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/kernel/freertos" \
    "-I$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/posix/ticlang" \
    -I${FREERTOS_INSTALL_DIR}/FreeRTOS/Source/include \
    -I${FREERTOS_INSTALL_DIR}/FreeRTOS/Source/portable/GCC/ARM_CM33/non_secure \
    -gdwarf-3 \
    -mcpu=cortex-m33 \
    -mfloat-abi=hard \
    -mfpu=fpv5-sp-d16

LFLAGS =  \
    --define=NVOCMP_NVPAGES=2 \
    "-i$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source" \
     --diag_suppress=10063 --define=FREERTOS \
    ti_utils_build_linker.cmd.genlibs \
    -lti/devices/cc13x4_cc26x4/driverlib/bin/ticlang/driverlib.lib \
    ../../freertos/ticlang/cc13x4_cc26x4.cmd \
    "-Wl,-m,$(NAME).map" \
    -Wl,--rom_model \
    -Wl,--warn_sections \
    "-L$(TICLANG_ARMCOMPILER)/lib" \
    -llibc.a
all: $(NAME).out

.INTERMEDIATE: syscfg
$(SYSCFG_FILES): syscfg
	@ echo generation complete

syscfg: ../../freertos/sensor.syscfg
	@ echo Generating configuration files...
	@ $(SYSCFG_CMD_STUB) --output $(@D) $<

define C_RULE
$(basename $(notdir $(1))).obj: $(1) $(SYSCFG_H_FILES)
	@ echo Building $$@
	@ $(CC) $(CFLAGS) -c $$< -o $$@
endef

$(foreach c_file,$(SYSCFG_C_FILES),$(eval $(call C_RULE,$(c_file))))

application_main.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/sensor/main.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

application_sensor_sensor.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/sensor/sensor.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

application_sensor_ssf.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/sensor/ssf.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

application_sensor_link_controller_jdllc.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/../../../../source/ti/ti154stack/common/jdllc/jdllc.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

software_stack_ti15_4stack_mac_mac_settings_mac_user_config.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/../../../../source/ti/ti154stack/common/boards/mac_user_config.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

application_cui_cui.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/../../../../source/ti/common/cui/cui.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

application_sensor_sm_sm_ti154.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/../../../../source/ti/ti154stack/common/sm/sm_ti154.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

application_sensor_sm_sm_ecc_ti154.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/../../../../source/ti/ti154stack/common/sm/sm_ecc_ti154.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

application_sensor_sm_sm_toolbox.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/../../../../source/ti/ti154stack/common/sm/sm_toolbox.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

software_stack_ti15_4stack_nv_crc.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/../../../../source/ti/common/nv/crc.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

software_stack_ti15_4stack_nv_nvocmp.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/../../../../source/ti/common/nv/nvocmp.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

software_stack_ti15_4stack_mac_low_level_mac_activity.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/../../../../source/ti/ti154stack/low_level/cc13xx/mac_activity.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

software_stack_ti15_4stack_mac_mac_settings_mac_cfg.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/../../../../source/ti/ti154stack/high_level/mac_cfg.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

software_stack_ti15_4stack_mac_mac_settings_mac_settings.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/../../../../source/ti/ti154stack/low_level/cc13xx/mac_settings.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

software_stack_ti15_4stack_mac_macTask.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/../../../../source/ti/ti154stack/common/osal_port/osal_port_posix/macTask.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

software_stack_ti15_4stack_mac_api_mac.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/ti154stack/apps/../../../../source/ti/ti154stack/common/osal_port/osal_port_posix/api_mac.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

$(NAME).out: $(OBJECTS)
	@ echo linking $@
	@ $(LNK) -Wl,-u,_c_int00 $(OBJECTS)  $(LFLAGS) -o $(NAME).out

clean:
	@ echo Cleaning...
	@ $(RM) $(OBJECTS) > $(DEVNULL) 2>&1
	@ $(RM) $(NAME).out > $(DEVNULL) 2>&1
	@ $(RM) $(NAME).map > $(DEVNULL) 2>&1
	@ $(RM) $(SYSCFG_FILES)> $(DEVNULL) 2>&1
