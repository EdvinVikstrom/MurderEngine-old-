# CMake generated Testfile for 
# Source directory: /home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang
# Build directory: /home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(glslang-testsuite "bash" "runtests" "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/localResults" "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/StandAlone/glslangValidator" "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/build/StandAlone/spirv-remap")
set_tests_properties(glslang-testsuite PROPERTIES  WORKING_DIRECTORY "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/Test/" _BACKTRACE_TRIPLES "/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/CMakeLists.txt;211;add_test;/home/edvinskomputa/Dokument/OnePunchEngine/src/external/vulkan/source/glslang/CMakeLists.txt;0;")
subdirs("External")
subdirs("glslang")
subdirs("OGLCompilersDLL")
subdirs("StandAlone")
subdirs("SPIRV")
subdirs("hlsl")
subdirs("gtests")
