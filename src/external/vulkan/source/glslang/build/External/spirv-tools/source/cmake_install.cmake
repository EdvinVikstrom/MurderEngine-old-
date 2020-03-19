# Install script for directory: /home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/External/spirv-tools/source

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/libSPIRV-Tools.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib" TYPE STATIC_LIBRARY FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/source/libSPIRV-Tools.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/libSPIRV-Tools-shared.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/libSPIRV-Tools-shared.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/libSPIRV-Tools-shared.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/libSPIRV-Tools-shared.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib" TYPE SHARED_LIBRARY FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/source/libSPIRV-Tools-shared.so")
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/libSPIRV-Tools-shared.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/libSPIRV-Tools-shared.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/libSPIRV-Tools-shared.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/SPIRV-Tools/SPIRV-ToolsTarget.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/SPIRV-Tools/SPIRV-ToolsTarget.cmake"
         "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/source/CMakeFiles/Export/_home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/SPIRV-Tools/SPIRV-ToolsTarget.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/SPIRV-Tools/SPIRV-ToolsTarget-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/SPIRV-Tools/SPIRV-ToolsTarget.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/SPIRV-Tools/SPIRV-ToolsTarget.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/SPIRV-Tools" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/source/CMakeFiles/Export/_home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/SPIRV-Tools/SPIRV-ToolsTarget.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/SPIRV-Tools/SPIRV-ToolsTarget-release.cmake")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/SPIRV-Tools" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/source/CMakeFiles/Export/_home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/SPIRV-Tools/SPIRV-ToolsTarget-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/SPIRV-Tools/SPIRV-ToolsConfig.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/SPIRV-Tools" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/SPIRV-ToolsConfig.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/source/opt/cmake_install.cmake")
  include("/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/source/reduce/cmake_install.cmake")
  include("/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/source/fuzz/cmake_install.cmake")
  include("/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/source/link/cmake_install.cmake")

endif()

