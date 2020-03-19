#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "OSDependent" for configuration "Release"
set_property(TARGET OSDependent APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(OSDependent PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/libOSDependent.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS OSDependent )
list(APPEND _IMPORT_CHECK_FILES_FOR_OSDependent "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/libOSDependent.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
