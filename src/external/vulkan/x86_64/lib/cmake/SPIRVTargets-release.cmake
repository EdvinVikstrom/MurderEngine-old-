#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SPIRV" for configuration "Release"
set_property(TARGET SPIRV APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SPIRV PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/libSPIRV.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS SPIRV )
list(APPEND _IMPORT_CHECK_FILES_FOR_SPIRV "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/libSPIRV.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
