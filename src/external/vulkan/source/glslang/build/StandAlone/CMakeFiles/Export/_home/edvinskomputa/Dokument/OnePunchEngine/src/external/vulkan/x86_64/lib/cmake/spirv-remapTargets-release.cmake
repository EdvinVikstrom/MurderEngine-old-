#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "spirv-remap" for configuration "Release"
set_property(TARGET spirv-remap APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(spirv-remap PROPERTIES
  IMPORTED_LOCATION_RELEASE "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-remap"
  )

list(APPEND _IMPORT_CHECK_TARGETS spirv-remap )
list(APPEND _IMPORT_CHECK_FILES_FOR_spirv-remap "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-remap" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
