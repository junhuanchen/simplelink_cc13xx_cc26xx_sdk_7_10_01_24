#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ThirdPartySpiffs::spiffs_m4f" for configuration "Release"
set_property(TARGET ThirdPartySpiffs::spiffs_m4f APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ThirdPartySpiffs::spiffs_m4f PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/source/third_party/spiffs/lib/iar/m4f/spiffs.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS ThirdPartySpiffs::spiffs_m4f )
list(APPEND _IMPORT_CHECK_FILES_FOR_ThirdPartySpiffs::spiffs_m4f "${_IMPORT_PREFIX}/source/third_party/spiffs/lib/iar/m4f/spiffs.a" )

# Import target "ThirdPartySpiffs::spiffs_m4f_cc26xx" for configuration "Release"
set_property(TARGET ThirdPartySpiffs::spiffs_m4f_cc26xx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ThirdPartySpiffs::spiffs_m4f_cc26xx PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/source/third_party/spiffs/lib/iar/m4f/spiffs_cc26xx.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS ThirdPartySpiffs::spiffs_m4f_cc26xx )
list(APPEND _IMPORT_CHECK_FILES_FOR_ThirdPartySpiffs::spiffs_m4f_cc26xx "${_IMPORT_PREFIX}/source/third_party/spiffs/lib/iar/m4f/spiffs_cc26xx.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
