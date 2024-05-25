# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "D:/FiPPP;D:/FiPPP/cmake-build-debug-tdm_gcc103")
set(CPACK_CMAKE_GENERATOR "Ninja")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.13)")
set(CPACK_DEBIAN_PACKAGE_SECTION "science")
set(CPACK_DEBIAN_SECTION "stable")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "D:/SoftWare/CLion 2022.3.1/bin/cmake/win/share/cmake-3.24/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "FiPPP built using CMake")
set(CPACK_GENERATOR "NSIS;ZIP")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY "OFF")
set(CPACK_INSTALL_CMAKE_PROJECTS "D:/FiPPP/cmake-build-debug-tdm_gcc103;FiPPP;ALL;/")
set(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/FiPPP")
set(CPACK_MODULE_PATH "")
set(CPACK_NSIS_DISPLAY_NAME "gpstk")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_PACKAGE_NAME "gpstk")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "D:/FiPPP/cmake-build-debug-tdm_gcc103/CPackConfig.cmake")
set(CPACK_PACKAGE_CONTACT "Bryan Parsons <bparsons@arlut.utexas.edu>")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "D:/SoftWare/CLion 2022.3.1/bin/cmake/win/share/cmake-3.24/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Libraries and applications for the GNSS processing GPSTk toolkit.")
set(CPACK_PACKAGE_FILE_NAME "FiPPP--win64")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "gpstk")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "gpstk")
set(CPACK_PACKAGE_NAME "FiPPP")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "ARL:UT SGL")
set(CPACK_PACKAGE_VERSION "")
set(CPACK_PACKAGE_VERSION_MAJOR "")
set(CPACK_PACKAGE_VERSION_MINOR "")
set(CPACK_PACKAGE_VERSION_PATCH "")
set(CPACK_RESOURCE_FILE_LICENSE "D:/SoftWare/CLion 2022.3.1/bin/cmake/win/share/cmake-3.24/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "D:/SoftWare/CLion 2022.3.1/bin/cmake/win/share/cmake-3.24/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "D:/SoftWare/CLion 2022.3.1/bin/cmake/win/share/cmake-3.24/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_IGNORE_FILES "build/;build-.*/;examples/;ref/;.*/[.].*")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "D:/FiPPP/cmake-build-debug-tdm_gcc103/CPackSourceConfig.cmake")
set(CPACK_STRIP_FILES "1")
set(CPACK_SYSTEM_NAME "win64")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "gpstk")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "D:/FiPPP/cmake-build-debug-tdm_gcc103/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()