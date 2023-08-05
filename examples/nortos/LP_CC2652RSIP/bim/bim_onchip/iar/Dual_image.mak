CFLAGS += -DBIM_ONCHIP \    -DAUTHENTICATE_PERSISTENT_IMG \
    -DxDEBUG_BIM \
    -DSECURITY \
    -DBIM_DUAL_ONCHIP_IMAGE \
    -DxFEATURE_SWITCH_VALID_IMAGES \
    -DxBIM_ERASE_INVALID_IMAGE \
    -DxBIM_BLINK_LED_NO_VALID_IMAGE \
    -I$COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR$/source/ti/common/cc26xx/sha2 \
    -I$COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR$/source/ti/common/cc26xx/ecc \
    -I$COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR$/source/ti/common/cc26xx/oad \
    -I$COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR$/source/ti/common/cc26xx/crc \
    -I$COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR$/source/ti/common/cc26xx/flash_interface

LFLAGS += $COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR$/source/ti/ble5stack/rom/ble_rom_releases/cc26x2_v2_pg2/Final_Release/ble_rom.symbols
OBJECTS += Application_sign_util.obj Application_sha2_driverlib.obj
