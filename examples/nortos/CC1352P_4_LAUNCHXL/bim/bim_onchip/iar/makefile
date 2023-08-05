COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR ?= $(abspath ../../../../../..)

include $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/imports.mak

CC = "$(IAR_ARMCOMPILER)/bin/iccarm"
LNK = "$(IAR_ARMCOMPILER)/bin/ilinkarm"

OBJECTS = Application_bim_onchip_main.obj Application_ccfg_app.obj Application_bim_util.obj Application_crc32.obj Application_led_debug.obj Application_flash_interface_internal.obj SPI_bsp_spi_cc13x2_cc26x2.obj Application_startup_iar.obj
NAME = bim_onchip

CFLAGS = -I.. \
    -Ohz \
    -I$COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR$/source \
    -I$COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR$/source \
    -I$COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR$/source/ti \
    -I$COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR$/source/ti/common/flash/no_rtos/extFlash \
    -DDeviceFamily_CC13X2 \
    -I$COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR$/source/ti/devices/cc13x2_cc26x2/startup_files \
    -DSET_CCFG_IMAGE_VALID_CONF_IMAGE_VALID=0x56000 \
    -DSET_CCFG_MODE_CONF_XOSC_CAP_MOD=0x0 \
    -DSET_CCFG_MODE_CONF_XOSC_CAPARRAY_DELTA=-63 \
    --debug \
    --silent \
    -e \
    --aeabi \
    --thumb \
    --diag_suppress=Pa050 \
    --cpu Cortex-M4 \
    --fpu=VFPv4_sp \
    --vla

LFLAGS = --config_def xPAGE_ALIGN=1 --inline \
    -L$COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR$/source/ti/devices/cc13x2_cc26x2 \
    -L$COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR$/source/ti/devices/cc13x2_cc26x2/inc \
    -L$COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR$/source/ti/devices/cc13x2_cc26x2/driverlib \
    "$(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/devices/cc13x2_cc26x2/driverlib/bin/iar/driverlib.lib" \
    --config ../bim_cc26x2_cc13x2.icf \
    --map "$(NAME).map" \
    --silent \
    --semihosting=iar_breakpoint \
    --cpu=Cortex-M4 \
    --fpu=VFPv4_sp

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
	@ $(CC) $(CFLAGS) $< -o $@

Application_ccfg_app.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/bim/ccfg_app.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) $< -o $@

Application_bim_util.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/cc26xx/bim/bim_util.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) $< -o $@

Application_crc32.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/cc26xx/crc/crc32.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) $< -o $@

Application_led_debug.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/cc26xx/debug/led_debug.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) $< -o $@

Application_sign_util.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/cc26xx/ecc/sign_util.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) $< -o $@

Application_sha2_driverlib.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/cc26xx/sha2/sha2_driverlib.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) $< -o $@

Application_flash_interface_internal.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/cc26xx/flash_interface/internal/flash_interface_internal.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) $< -o $@

SPI_bsp_spi_cc13x2_cc26x2.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/common/flash/no_rtos/extFlash/bsp_spi_cc13x2_cc26x2.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) $< -o $@

Application_startup_iar.obj: $(COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/source/ti/devices/cc13x2_cc26x2/startup_files/startup_iar.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) $< -o $@

$(NAME).out: $(OBJECTS)
	@ echo linking $@
	@ $(LNK)  $(OBJECTS)  $(LFLAGS) -o $(NAME).out

clean:
	@ echo Cleaning...
	@ $(RM) $(OBJECTS) > $(DEVNULL) 2>&1
	@ $(RM) $(NAME).out > $(DEVNULL) 2>&1
	@ $(RM) $(NAME).map > $(DEVNULL) 2>&1
