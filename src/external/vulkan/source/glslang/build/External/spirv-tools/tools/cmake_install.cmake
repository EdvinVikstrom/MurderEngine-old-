# Install script for directory: /home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/External/spirv-tools/tools

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
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-as" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-as")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-as"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-as")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin" TYPE EXECUTABLE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/tools/spirv-as")
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-as" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-as")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-as")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-dis" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-dis")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-dis"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-dis")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin" TYPE EXECUTABLE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/tools/spirv-dis")
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-dis" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-dis")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-dis")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-val" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-val")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-val"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-val")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin" TYPE EXECUTABLE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/tools/spirv-val")
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-val" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-val")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-val")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-opt" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-opt")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-opt"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-opt")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin" TYPE EXECUTABLE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/tools/spirv-opt")
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-opt" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-opt")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-opt")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-cfg" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-cfg")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-cfg"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-cfg")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin" TYPE EXECUTABLE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/tools/spirv-cfg")
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-cfg" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-cfg")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-cfg")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-link" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-link")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-link"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-link")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin" TYPE EXECUTABLE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/tools/spirv-link")
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-link" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-link")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-link")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-reduce" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-reduce")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-reduce"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-reduce")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin" TYPE EXECUTABLE FILES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/tools/spirv-reduce")
  if(EXISTS "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-reduce" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-reduce")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/x86_64/bin/spirv-reduce")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/tools/lesspipe/cmake_install.cmake")
  include("/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/External/spirv-tools/tools/emacs/cmake_install.cmake")

endif()

