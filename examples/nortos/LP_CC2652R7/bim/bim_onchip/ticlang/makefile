COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR ?= $(abspath ../../../../../..)

include $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/imports.mak

CC = "$(TICLANG_ARMCOMPILER)/bin/tiarmclang"
LNK = "$(TICLANG_ARMCOMPILER)/bin/tiarmclang"

OBJECTS = Application_bim_onchip_main.obj Application_ccfg_app.obj Application_bim_util.obj Application_crc32.obj Application_led_debug.obj Application_flash_interface_internal.obj SPI_bsp_spi_cc13x2_cc26x2.obj Application_startup_ticlang.obj
NAME = bim_onchip

CFLAGS = -I.. \
    -Oz \
    -mlittle-endian \
    -fshort-enums \
    -munaligned-access \
    -funsigned-char \
    -fcommon \
    -ffunction-sections \
    -fdata-sections \
    -std=gnu9x \
    -I${CG_TOOL_ROOT}/include \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/common/flash/no_rtos/extFlash \
    -DDeviceFamily_CC26X2X7 \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/devices/cc13x2x7_cc26x2x7/startup_files \
    -DSET_CCFG_IMAGE_VALID_CONF_IMAGE_VALID=0xAE000 \
    -gdwarf-3 \
    -mcpu=cortex-m4 \
    -march=armv7e-m \
    -mthumb \
    -mfloat-abi=hard \
    -mfpu=fpv4-sp-d16

LFLAGS = --stack_size=256 \
    --unused_section_elimination=on \
    --diag_wrap=off \
    --xml_link_info=${ProjName}_linkInfo.xml \
    -x \
    --warn_sections \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/devices/cc13x2x7_cc26x2x7 \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/devices/cc13x2x7_cc26x2x7/inc \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/devices/cc13x2x7_cc26x2x7/driverlib \
    "-l$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/devices/cc13x2x7_cc26x2x7/driverlib/bin/ticlang/driverlib.lib" \
    ../bim_cc26x2x7_cc13x2x7.cmd \
    "-Wl,-m,$(NAME).map" \
    -Wl,--rom_model \
    -Wl,--warn_sections \
    "-L$(TICLANG_ARMCOMPILER)/lib" \
    -llibc.a

CONFIG := DEBUG_UNSECURE
ifeq ($(CONFIG), DEBUG_UNSECURE)
	include Debug_unsecure.mak
else ifeq ($(CONFIG), RELEASE_UNSECURE)
	include Release_unsecure.mak
else ifeq ($(CONFIG), RELEASE)
	include Release.mak
else ifeq ($(CONFIG), DEBUG)
	include Debug.mak
else ifeq ($(CONFIG), DUAL_IMAGE)
	include Dual_image.mak
endif

all: $(NAME).out

Application_bim_onchip_main.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/bim/bim_onchip_main.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

Application_ccfg_app.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/bim/ccfg_app.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

Application_bim_util.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/cc26xx/bim/bim_util.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

Application_crc32.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/cc26xx/crc/crc32.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

Application_led_debug.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/cc26xx/debug/led_debug.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

Application_sign_util.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/cc26xx/ecc/sign_util.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

Application_sha2_driverlib.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/cc26xx/sha2/sha2_driverlib.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

Application_flash_interface_internal.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/cc26xx/flash_interface/internal/flash_interface_internal.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

SPI_bsp_spi_cc13x2_cc26x2.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/flash/no_rtos/extFlash/bsp_spi_cc13x2_cc26x2.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

Application_startup_ticlang.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/devices/cc13x2x7_cc26x2x7/startup_files/startup_ticlang.c
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
