PROJECT_LOC = $(abspath ../../)
PROJECT_ROOT = $(PROJECT_LOC)
COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR ?= $(abspath ../../../../../../..)

include $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/imports.mak

CC = "$(TICLANG_ARMCOMPILER)/bin/tiarmclang"
LNK = "$(TICLANG_ARMCOMPILER)/bin/tiarmclang"

SYSCFG_CMD_STUB = $(SYSCONFIG_TOOL) --compiler ticlang --product $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/.metadata/product.json
SYSCFG_FILES := $(shell $(SYSCFG_CMD_STUB) --listGeneratedFiles --listReferencedFiles --output . ../../tirtos7/sensor.syscfg)

SYSCFG_C_FILES = $(filter %.c,$(SYSCFG_FILES))
SYSCFG_H_FILES = $(filter %.h,$(SYSCFG_FILES))

OBJECTS = application_main.obj application_sensor_sensor.obj application_sensor_ssf.obj application_sensor_link_controller_jdllc.obj software_stack_ti15_4stack_mac_mac_settings_mac_user_config.obj application_cui_cui.obj software_stack_ti15_4stack_nv_crc.obj software_stack_ti15_4stack_nv_nvocmp.obj software_stack_ti15_4stack_mac_low_level_mac_activity.obj software_stack_ti15_4stack_mac_mac_settings_mac_cfg.obj software_stack_ti15_4stack_mac_mac_settings_mac_settings.obj software_stack_ti15_4stack_mac_macTask.obj software_stack_ti15_4stack_mac_api_mac.obj $(patsubst %.c,%.obj,$(notdir $(SYSCFG_C_FILES)))
NAME = sensor_2_4g

CFLAGS = -I../.. \
    -I. \
    @${PROJECT_LOC}/application/defines/sensor_2_4g.opts \
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
    -DTIMAC_ROM_IMAGE_BUILD \
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
    @${CURDIR}/ti_154stack_config.opts \
    -DBoard_EXCLUDE_NVS_EXTERNAL_FLASH \
    -DDeviceFamily_CC13X2X7 \
    "-I$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source" \
    "-I$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/devices/cc13x2x7_cc26x2x7" \
    "-I$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/devices/cc13x2x7_cc26x2x7/inc" \
    "-I$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/devices/cc13x2x7_cc26x2x7/driverlib" \
    "-I$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/posix/ticlang" \
    "-I$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/kernel/tirtos7/packages" \
    -gdwarf-3 \
    -mcpu=cortex-m4 \
    -march=armv7e-m \
    -mthumb \
    -mfloat-abi=hard \
    -mfpu=fpv4-sp-d16

LFLAGS = -Wl,--library=${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ti154stack/lib/rom/ticlang/timac_rom_PG2_0_rom_api_linker.cmd \
    -DNVOCMP_NVPAGES=2 \
    "-L$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source" \
    "-L$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/kernel/tirtos7/packages" \
    -DTIRTOS7 \
    -Wl,--unused_section_elimination=on \
    -Wl,--diag_wrap=off \
    -Wl,--xml_link_info=${ProjName}_linkInfo.xml \
    -Wl,-x \
    -Wl,--display_error_number \
    ti_utils_build_linker.cmd.genlibs \
    "-l$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/devices/cc13x2x7_cc26x2x7/driverlib/bin/ticlang/driverlib.lib" \
    ../../tirtos7/ticlang/cc13x2x7_cc26x2x7_tirtos7.cmd \
    "-Wl,-m,$(NAME).map" \
    -Wl,--rom_model \
    -Wl,--warn_sections \
    "-L$(TICLANG_ARMCOMPILER)/lib" \
    -llibc.a
all: $(NAME).out

.INTERMEDIATE: syscfg
$(SYSCFG_FILES): syscfg
	@ echo generation complete

syscfg: ../../tirtos7/sensor.syscfg
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
