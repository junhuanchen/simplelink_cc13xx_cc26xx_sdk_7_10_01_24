SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR ?= $(abspath ../../../../..)

include $(SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR)/imports.mak

CC = "$(TICLANG_ARMCOMPILER)/bin/tiarmclang"
AR = "$(TICLANG_ARMCOMPILER)/bin/tiarmar"

OBJECTS = src_ncp_changed_props_set.obj src_ncp_example_vendor_hook.obj src_ncp_ncp_base.obj src_ncp_ncp_base_dispatcher.obj src_ncp_ncp_base_ftd.obj src_ncp_ncp_base_mtd.obj src_ncp_ncp_base_radio.obj src_ncp_ncp_hdlc.obj src_ncp_ncp_spi.obj src_lib_hdlc_hdlc.obj src_lib_spinel_spinel.obj src_lib_spinel_spinel_buffer.obj src_lib_spinel_spinel_decoder.obj src_lib_spinel_spinel_encoder.obj
NAME = libopenthread_ncp_ftd

CFLAGS = -I../../.. \
    -Oz \
    -g \
    -gdwarf-3 \
    -Wall \
    -Wno-ti-macros \
    -ffunction-sections \
    -Wextra \
    -Wshadow \
    -Werror \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/third_party/openthread/examples/platforms \
    -DHAVE_CONFIG_H -D_BSD_SOURCE=1 -D_DEFAULT_SOURCE=1 \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/third_party/openthread/third_party/mbedtls \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/third_party/openthread/third_party/mbedtls/repo/include \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/third_party/openthread/include \
    -DMBEDTLS_CONFIG_FILE='"mbedtls-config-cc13x4_26x4.h"' \
    -I${WorkspaceDirPath}/libmbedcrypto_cc13x4_26x4_ticlang/config \
    -DDeviceFamily_CC13X4_CC26X4 \
    -DOPENTHREAD_FTD=1 \
    -DOPENTHREAD_SPINEL_CONFIG_OPENTHREAD_MESSAGE_ENABLE=1 \
    -DOPENTHREAD_PROJECT_CORE_CONFIG_FILE='"openthread-core-cc13x4_26x4-config.h"' \
    -DOPENTHREAD_CONFIG_FILE='"openthread-config-cc13x4_26x4-ftd.h"' \
    -I${WorkspaceDirPath}/libopenthread_ftd_cc13x4_26x4_ticlang/config \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/third_party/openthread/src/core \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/third_party/openthread/src \
    -mcpu=cortex-m33 \
    -mfloat-abi=hard \
    -mfpu=fpv5-sp-d16

CPPFLAGS = -I../../.. \
    -Oz \
    -g \
    -gdwarf-3 \
    -Wall \
    -Wno-ti-macros \
    -ffunction-sections \
    -Wextra \
    -Wshadow \
    -Werror \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/third_party/openthread/examples/platforms \
    -DHAVE_CONFIG_H -D_BSD_SOURCE=1 -D_DEFAULT_SOURCE=1 \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/third_party/openthread/third_party/mbedtls \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/third_party/openthread/third_party/mbedtls/repo/include \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/third_party/openthread/include \
    -DMBEDTLS_CONFIG_FILE='"mbedtls-config-cc13x4_26x4.h"' \
    -I${WorkspaceDirPath}/libmbedcrypto_cc13x4_26x4_ticlang/config \
    -DDeviceFamily_CC13X4_CC26X4 \
    -DOPENTHREAD_FTD=1 \
    -DOPENTHREAD_SPINEL_CONFIG_OPENTHREAD_MESSAGE_ENABLE=1 \
    -DOPENTHREAD_PROJECT_CORE_CONFIG_FILE='"openthread-core-cc13x4_26x4-config.h"' \
    -DOPENTHREAD_CONFIG_FILE='"openthread-config-cc13x4_26x4-ftd.h"' \
    -I${WorkspaceDirPath}/libopenthread_ftd_cc13x4_26x4_ticlang/config \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/third_party/openthread/src/core \
    -I${COM_TI_SIMPLELINK_CC13XX_CC26XX_SDK_INSTALL_DIR}/source/third_party/openthread/src \
    -mcpu=cortex-m33 \
    -mfloat-abi=hard \
    -mfpu=fpv5-sp-d16

all: $(NAME).a

src_lib_spinel_spinel.obj: OPENTHREAD_MAKE_PATH/src/lib/spinel/spinel.c
	@ echo Building $@
	@ $(CC) $(CFLAGS) -c $< -o $@

src_ncp_changed_props_set.obj: OPENTHREAD_MAKE_PATH/src/ncp/changed_props_set.cpp
	@ echo Building $@
	@ $(CC) $(CPPFLAGS) -c $< -o $@

src_ncp_example_vendor_hook.obj: OPENTHREAD_MAKE_PATH/src/ncp/example_vendor_hook.cpp
	@ echo Building $@
	@ $(CC) $(CPPFLAGS) -c $< -o $@

src_ncp_ncp_base.obj: OPENTHREAD_MAKE_PATH/src/ncp/ncp_base.cpp
	@ echo Building $@
	@ $(CC) $(CPPFLAGS) -c $< -o $@

src_ncp_ncp_base_dispatcher.obj: OPENTHREAD_MAKE_PATH/src/ncp/ncp_base_dispatcher.cpp
	@ echo Building $@
	@ $(CC) $(CPPFLAGS) -c $< -o $@

src_ncp_ncp_base_ftd.obj: OPENTHREAD_MAKE_PATH/src/ncp/ncp_base_ftd.cpp
	@ echo Building $@
	@ $(CC) $(CPPFLAGS) -c $< -o $@

src_ncp_ncp_base_mtd.obj: OPENTHREAD_MAKE_PATH/src/ncp/ncp_base_mtd.cpp
	@ echo Building $@
	@ $(CC) $(CPPFLAGS) -c $< -o $@

src_ncp_ncp_base_radio.obj: OPENTHREAD_MAKE_PATH/src/ncp/ncp_base_radio.cpp
	@ echo Building $@
	@ $(CC) $(CPPFLAGS) -c $< -o $@

src_ncp_ncp_hdlc.obj: OPENTHREAD_MAKE_PATH/src/ncp/ncp_hdlc.cpp
	@ echo Building $@
	@ $(CC) $(CPPFLAGS) -c $< -o $@

src_ncp_ncp_spi.obj: OPENTHREAD_MAKE_PATH/src/ncp/ncp_spi.cpp
	@ echo Building $@
	@ $(CC) $(CPPFLAGS) -c $< -o $@

src_lib_hdlc_hdlc.obj: OPENTHREAD_MAKE_PATH/src/lib/hdlc/hdlc.cpp
	@ echo Building $@
	@ $(CC) $(CPPFLAGS) -c $< -o $@

src_lib_spinel_spinel_buffer.obj: OPENTHREAD_MAKE_PATH/src/lib/spinel/spinel_buffer.cpp
	@ echo Building $@
	@ $(CC) $(CPPFLAGS) -c $< -o $@

src_lib_spinel_spinel_decoder.obj: OPENTHREAD_MAKE_PATH/src/lib/spinel/spinel_decoder.cpp
	@ echo Building $@
	@ $(CC) $(CPPFLAGS) -c $< -o $@

src_lib_spinel_spinel_encoder.obj: OPENTHREAD_MAKE_PATH/src/lib/spinel/spinel_encoder.cpp
	@ echo Building $@
	@ $(CC) $(CPPFLAGS) -c $< -o $@

$(NAME).a: $(OBJECTS)
	@ echo creating library $@
	@ $(AR) r $@ $^

clean:
	@ echo Cleaning...
	@ $(RM) $(OBJECTS) > $(DEVNULL) 2>&1
	@ $(RM) $(NAME).a > $(DEVNULL) 2>&1
