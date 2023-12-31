SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR ?= $(abspath ../../../../../../..)

include $(SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/imports.mak

CC = "$(TICLANG_ARMCOMPILER)/bin/tiarmclang"
LNK = "$(TICLANG_ARMCOMPILER)/bin/tiarmclang"

SYSCFG_CMD_STUB = $(SYSCONFIG_TOOL) --compiler ticlang --product $(SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/.metadata/product.json
SYSCFG_FILES := $(shell $(SYSCFG_CMD_STUB) --listGeneratedFiles --listReferencedFiles --output . ../../tirtos7/shade.syscfg)

SYSCFG_C_FILES = $(filter %.c,$(SYSCFG_FILES))
SYSCFG_H_FILES = $(filter %.h,$(SYSCFG_FILES))

OBJECTS = platform_alarm.obj platform_alarm_micro.obj platform_diag.obj platform_entropy.obj platform_misc.obj platform_settings.obj platform_system.obj platform_radio.obj platform_uart.obj platform_nv_crc.obj platform_nv_nvocmp.obj images.obj tiop_ui.obj cui.obj disp_utils.obj shade.obj main.obj otstack.obj otsupport_otrtosapi.obj $(patsubst %.c,%.obj,$(notdir $(SYSCFG_C_FILES)))
NAME = shade

CFLAGS = -I../.. \
    -I. \
    -Oz \
    -g \
    -gdwarf-3 \
    -Wall \
    -Wno-ti-macros \
    -DHAVE_CONFIG_H \
    -DBoard_EXCLUDE_NVS_EXTERNAL_FLASH \
    -DNVOCMP_POSIX_MUTEX \
    -DNVOCMP_NVPAGES=2 \
    -DNDEBUG \
    -DBOARD_DISPLAY_USE_UART=1 \
    -DMBEDTLS_CONFIG_FILE='"mbedtls-config-cc13x4_26x4.h"' \
    "-I$(SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/thread/cc13x4_26x4/libmbedcrypto/config" \
    -IOPENTHREAD_MAKE_PATH/examples/platforms \
    -IOPENTHREAD_MAKE_PATH/include \
    -IOPENTHREAD_MAKE_PATH/src/core \
    -IOPENTHREAD_MAKE_PATH/src \
    -IOPENTHREAD_MAKE_PATH/third_party/mbedtls/repo/include \
    -IC:/.conan/26dfac/1/external/source \
    -I${PROJECT_ROOT}/platform/crypto \
    -DOPENTHREAD_MTD=1 \
    "-I$(SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/thread/cc13x4_26x4/libopenthread_mtd/config" \
    -DOPENTHREAD_CONFIG_FILE='"openthread-config-cc13x4_26x4-mtd.h"' \
    -DOPENTHREAD_PROJECT_CORE_CONFIG_FILE='"openthread-core-cc13x4_26x4-config.h"' \
    -DTIOP_CUI=1 \
    -DCUI_POSIX=1 \
    -DBOARD_DISPLAY_USE_LCD=0 \
    -DDeviceFamily_CC13X4 \
    "-I$(SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source" \
    "-I$(SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/devices/cc13x4_cc26x4" \
    "-I$(SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/posix/ticlang" \
    "-I$(SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/kernel/tirtos7/packages" \
    -mcpu=cortex-m33 \
    -mfloat-abi=hard \
    -mfpu=fpv5-sp-d16

LFLAGS = "-Wl,-i$(SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/thread/cc13x4_26x4/libopenthread_mtd/lib/ticlang/m33f" \
    "-Wl,-i$(SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/thread/cc13x4_26x4/libopenthread_platform_utils_mtd/lib/ticlang/m33f" \
    "-Wl,-i$(SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/thread/cc13x4_26x4/libmbedcrypto/lib/ticlang/m33f" \
    -Wl,-llibopenthread_mtd.a \
    -Wl,-llibopenthread_platform_utils_mtd.a \
    -Wl,-llibmbedcrypto.a \
    -l${PROJECT_BUILD_DIR}/syscfg/ti_utils_build_linker.cmd.genlibs \
    "-L$(SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source" \
    -LC:/.conan/26dfac/1/external/source \
    "-L$(SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/kernel/tirtos7/packages" \
    -lti/devices/cc13x4_cc26x4/driverlib/bin/ticlang/driverlib.lib \
    ../../tirtos7/ticlang/cc13x4_cc26x4_tirtos7.cmd \
    "-Wl,-m,$(NAME).map" \
    -Wl,--rom_model \
    -Wl,--warn_sections \
    "-L$(TICLANG_ARMCOMPILER)/lib" \
    -llibc.a
all: $(NAME).out

.INTERMEDIATE: syscfg
$(SYSCFG_FILES): syscfg
	@ echo generation complete

syscfg: ../../tirtos7/shade.syscfg
	@ echo Generating configuration files...
	@ $(SYSCFG_CMD_STUB) --output $(@D) $<

define C_RULE
$(basename $(notdir $(1))).obj: $(1) $(SYSCFG_H_FILES)
	@ echo Building $$@
	@ $(CC) $(CFLAGS) -c $$< -o $$@
endef

$(foreach c_file,$(SYSCFG_C_FILES),$(eval $(call C_RULE,$(c_file))))

platform_alarm.obj: ../../platform/alarm.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

platform_alarm_micro.obj: ../../platform/alarm_micro.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

platform_diag.obj: ../../platform/diag.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

platform_entropy.obj: ../../platform/entropy.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

platform_misc.obj: ../../platform/misc.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

platform_settings.obj: ../../platform/settings.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

platform_system.obj: ../../platform/system.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

platform_radio.obj: ../../platform/radio.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

platform_uart.obj: ../../platform/uart.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

platform_nv_crc.obj: ../../platform/nv/crc.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

platform_nv_nvocmp.obj: ../../platform/nv/nvocmp.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

images.obj: ../../images.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

tiop_ui.obj: ../../tiop_ui.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

cui.obj: ../../cui.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

disp_utils.obj: ../../disp_utils.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

shade.obj: ../../shade.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

main.obj: ../../main.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

otstack.obj: ../../otstack.c $(SYSCFG_H_FILES)
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

otsupport_otrtosapi.obj: ../../otsupport/otrtosapi.c $(SYSCFG_H_FILES)
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
