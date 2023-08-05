CFLAGS += -DBOOT_LOADER \    -DxFLASH_DEVICE_ERASE \
    -DSECURITY \
    -DDEBUG_BIM \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/common/cc26xx/sha2 \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/common/cc26xx/ecc \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/common/cc26xx/oad \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/common/cc26xx/crc \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/common/cc26xx/flash_interface

LFLAGS += -l${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/ti/ble5stack/rom/ble_rom_releases/cc26x2_v2_pg2/Final_Release/ble_rom.symbols
OBJECTS += Application_sign_util.obj
