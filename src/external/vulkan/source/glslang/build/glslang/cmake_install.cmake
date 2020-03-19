# Install script for directory: /home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang

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
   "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/libglslang.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib" TYPE STATIC_LIBRARY FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/glslang/libglslang.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/glslangTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/glslangTargets.cmake"
         "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/glslang/CMakeFiles/Export/_home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/glslangTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/glslangTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/glslangTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/glslangTargets.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/glslang/CMakeFiles/Export/_home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/glslangTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/glslangTargets-release.cmake")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/glslang/CMakeFiles/Export/_home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/lib/cmake/glslangTargets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Public" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/Public/ShaderLang.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/Include/arrays.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/Include/BaseTypes.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/Include/Common.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/Include/ConstantUnion.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/Include/InfoSink.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/Include/InitializeGlobals.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/Include/intermediate.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/Include/PoolAlloc.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/Include/ResourceLimits.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/Include/revision.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/Include/ShHandle.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/Include/Types.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/attribute.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/glslang_tab.cpp.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/gl_types.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/Initialize.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/iomapper.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/LiveTraverser.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/localintermediate.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/ParseHelper.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/reflection.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/RemoveTree.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/Scan.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/ScanContext.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/SymbolTable.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/Versions.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/parseVersions.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/propagateNoContraction.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent/preprocessor" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/preprocessor/PpContext.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent/preprocessor" TYPE FILE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/glslang/MachineIndependent/preprocessor/PpTokens.h")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/glslang/OSDependent/Unix/cmake_install.cmake")

endif()

