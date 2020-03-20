# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/edvinskomputa/Dokument/OnePunchEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/edvinskomputa/Dokument/OnePunchEngine

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/edvinskomputa/Dokument/OnePunchEngine/CMakeFiles /home/edvinskomputa/Dokument/OnePunchEngine/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/edvinskomputa/Dokument/OnePunchEngine/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named MurderEngine

# Build rule for target.
MurderEngine: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 MurderEngine
.PHONY : MurderEngine

# fast build rule for target.
MurderEngine/fast:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/build
.PHONY : MurderEngine/fast

src/Main.o: src/Main.cpp.o

.PHONY : src/Main.o

# target to build an object file
src/Main.cpp.o:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/Main.cpp.o
.PHONY : src/Main.cpp.o

src/Main.i: src/Main.cpp.i

.PHONY : src/Main.i

# target to preprocess a source file
src/Main.cpp.i:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/Main.cpp.i
.PHONY : src/Main.cpp.i

src/Main.s: src/Main.cpp.s

.PHONY : src/Main.s

# target to generate assembly for a file
src/Main.cpp.s:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/Main.cpp.s
.PHONY : src/Main.cpp.s

src/engine/EngineManager.o: src/engine/EngineManager.cpp.o

.PHONY : src/engine/EngineManager.o

# target to build an object file
src/engine/EngineManager.cpp.o:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/EngineManager.cpp.o
.PHONY : src/engine/EngineManager.cpp.o

src/engine/EngineManager.i: src/engine/EngineManager.cpp.i

.PHONY : src/engine/EngineManager.i

# target to preprocess a source file
src/engine/EngineManager.cpp.i:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/EngineManager.cpp.i
.PHONY : src/engine/EngineManager.cpp.i

src/engine/EngineManager.s: src/engine/EngineManager.cpp.s

.PHONY : src/engine/EngineManager.s

# target to generate assembly for a file
src/engine/EngineManager.cpp.s:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/EngineManager.cpp.s
.PHONY : src/engine/EngineManager.cpp.s

src/engine/MurderEngine.o: src/engine/MurderEngine.cpp.o

.PHONY : src/engine/MurderEngine.o

# target to build an object file
src/engine/MurderEngine.cpp.o:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/MurderEngine.cpp.o
.PHONY : src/engine/MurderEngine.cpp.o

src/engine/MurderEngine.i: src/engine/MurderEngine.cpp.i

.PHONY : src/engine/MurderEngine.i

# target to preprocess a source file
src/engine/MurderEngine.cpp.i:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/MurderEngine.cpp.i
.PHONY : src/engine/MurderEngine.cpp.i

src/engine/MurderEngine.s: src/engine/MurderEngine.cpp.s

.PHONY : src/engine/MurderEngine.s

# target to generate assembly for a file
src/engine/MurderEngine.cpp.s:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/MurderEngine.cpp.s
.PHONY : src/engine/MurderEngine.cpp.s

src/engine/loaders/ImageReader.o: src/engine/loaders/ImageReader.cpp.o

.PHONY : src/engine/loaders/ImageReader.o

# target to build an object file
src/engine/loaders/ImageReader.cpp.o:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/loaders/ImageReader.cpp.o
.PHONY : src/engine/loaders/ImageReader.cpp.o

src/engine/loaders/ImageReader.i: src/engine/loaders/ImageReader.cpp.i

.PHONY : src/engine/loaders/ImageReader.i

# target to preprocess a source file
src/engine/loaders/ImageReader.cpp.i:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/loaders/ImageReader.cpp.i
.PHONY : src/engine/loaders/ImageReader.cpp.i

src/engine/loaders/ImageReader.s: src/engine/loaders/ImageReader.cpp.s

.PHONY : src/engine/loaders/ImageReader.s

# target to generate assembly for a file
src/engine/loaders/ImageReader.cpp.s:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/loaders/ImageReader.cpp.s
.PHONY : src/engine/loaders/ImageReader.cpp.s

src/engine/loaders/mesh_loader.o: src/engine/loaders/mesh_loader.cpp.o

.PHONY : src/engine/loaders/mesh_loader.o

# target to build an object file
src/engine/loaders/mesh_loader.cpp.o:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/loaders/mesh_loader.cpp.o
.PHONY : src/engine/loaders/mesh_loader.cpp.o

src/engine/loaders/mesh_loader.i: src/engine/loaders/mesh_loader.cpp.i

.PHONY : src/engine/loaders/mesh_loader.i

# target to preprocess a source file
src/engine/loaders/mesh_loader.cpp.i:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/loaders/mesh_loader.cpp.i
.PHONY : src/engine/loaders/mesh_loader.cpp.i

src/engine/loaders/mesh_loader.s: src/engine/loaders/mesh_loader.cpp.s

.PHONY : src/engine/loaders/mesh_loader.s

# target to generate assembly for a file
src/engine/loaders/mesh_loader.cpp.s:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/loaders/mesh_loader.cpp.s
.PHONY : src/engine/loaders/mesh_loader.cpp.s

src/engine/loaders/parsers/collada_parser.o: src/engine/loaders/parsers/collada_parser.cpp.o

.PHONY : src/engine/loaders/parsers/collada_parser.o

# target to build an object file
src/engine/loaders/parsers/collada_parser.cpp.o:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/loaders/parsers/collada_parser.cpp.o
.PHONY : src/engine/loaders/parsers/collada_parser.cpp.o

src/engine/loaders/parsers/collada_parser.i: src/engine/loaders/parsers/collada_parser.cpp.i

.PHONY : src/engine/loaders/parsers/collada_parser.i

# target to preprocess a source file
src/engine/loaders/parsers/collada_parser.cpp.i:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/loaders/parsers/collada_parser.cpp.i
.PHONY : src/engine/loaders/parsers/collada_parser.cpp.i

src/engine/loaders/parsers/collada_parser.s: src/engine/loaders/parsers/collada_parser.cpp.s

.PHONY : src/engine/loaders/parsers/collada_parser.s

# target to generate assembly for a file
src/engine/loaders/parsers/collada_parser.cpp.s:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/loaders/parsers/collada_parser.cpp.s
.PHONY : src/engine/loaders/parsers/collada_parser.cpp.s

src/engine/math/maths.o: src/engine/math/maths.cpp.o

.PHONY : src/engine/math/maths.o

# target to build an object file
src/engine/math/maths.cpp.o:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/math/maths.cpp.o
.PHONY : src/engine/math/maths.cpp.o

src/engine/math/maths.i: src/engine/math/maths.cpp.i

.PHONY : src/engine/math/maths.i

# target to preprocess a source file
src/engine/math/maths.cpp.i:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/math/maths.cpp.i
.PHONY : src/engine/math/maths.cpp.i

src/engine/math/maths.s: src/engine/math/maths.cpp.s

.PHONY : src/engine/math/maths.s

# target to generate assembly for a file
src/engine/math/maths.cpp.s:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/math/maths.cpp.s
.PHONY : src/engine/math/maths.cpp.s

src/engine/math/vectors.o: src/engine/math/vectors.cpp.o

.PHONY : src/engine/math/vectors.o

# target to build an object file
src/engine/math/vectors.cpp.o:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/math/vectors.cpp.o
.PHONY : src/engine/math/vectors.cpp.o

src/engine/math/vectors.i: src/engine/math/vectors.cpp.i

.PHONY : src/engine/math/vectors.i

# target to preprocess a source file
src/engine/math/vectors.cpp.i:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/math/vectors.cpp.i
.PHONY : src/engine/math/vectors.cpp.i

src/engine/math/vectors.s: src/engine/math/vectors.cpp.s

.PHONY : src/engine/math/vectors.s

# target to generate assembly for a file
src/engine/math/vectors.cpp.s:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/math/vectors.cpp.s
.PHONY : src/engine/math/vectors.cpp.s

src/engine/renderer/OpenGLApi.o: src/engine/renderer/OpenGLApi.cpp.o

.PHONY : src/engine/renderer/OpenGLApi.o

# target to build an object file
src/engine/renderer/OpenGLApi.cpp.o:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/renderer/OpenGLApi.cpp.o
.PHONY : src/engine/renderer/OpenGLApi.cpp.o

src/engine/renderer/OpenGLApi.i: src/engine/renderer/OpenGLApi.cpp.i

.PHONY : src/engine/renderer/OpenGLApi.i

# target to preprocess a source file
src/engine/renderer/OpenGLApi.cpp.i:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/renderer/OpenGLApi.cpp.i
.PHONY : src/engine/renderer/OpenGLApi.cpp.i

src/engine/renderer/OpenGLApi.s: src/engine/renderer/OpenGLApi.cpp.s

.PHONY : src/engine/renderer/OpenGLApi.s

# target to generate assembly for a file
src/engine/renderer/OpenGLApi.cpp.s:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/renderer/OpenGLApi.cpp.s
.PHONY : src/engine/renderer/OpenGLApi.cpp.s

src/engine/scene/scene.o: src/engine/scene/scene.cpp.o

.PHONY : src/engine/scene/scene.o

# target to build an object file
src/engine/scene/scene.cpp.o:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/scene/scene.cpp.o
.PHONY : src/engine/scene/scene.cpp.o

src/engine/scene/scene.i: src/engine/scene/scene.cpp.i

.PHONY : src/engine/scene/scene.i

# target to preprocess a source file
src/engine/scene/scene.cpp.i:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/scene/scene.cpp.i
.PHONY : src/engine/scene/scene.cpp.i

src/engine/scene/scene.s: src/engine/scene/scene.cpp.s

.PHONY : src/engine/scene/scene.s

# target to generate assembly for a file
src/engine/scene/scene.cpp.s:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/scene/scene.cpp.s
.PHONY : src/engine/scene/scene.cpp.s

src/engine/utilities/ArrayUtils.o: src/engine/utilities/ArrayUtils.cpp.o

.PHONY : src/engine/utilities/ArrayUtils.o

# target to build an object file
src/engine/utilities/ArrayUtils.cpp.o:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/utilities/ArrayUtils.cpp.o
.PHONY : src/engine/utilities/ArrayUtils.cpp.o

src/engine/utilities/ArrayUtils.i: src/engine/utilities/ArrayUtils.cpp.i

.PHONY : src/engine/utilities/ArrayUtils.i

# target to preprocess a source file
src/engine/utilities/ArrayUtils.cpp.i:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/utilities/ArrayUtils.cpp.i
.PHONY : src/engine/utilities/ArrayUtils.cpp.i

src/engine/utilities/ArrayUtils.s: src/engine/utilities/ArrayUtils.cpp.s

.PHONY : src/engine/utilities/ArrayUtils.s

# target to generate assembly for a file
src/engine/utilities/ArrayUtils.cpp.s:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/utilities/ArrayUtils.cpp.s
.PHONY : src/engine/utilities/ArrayUtils.cpp.s

src/engine/utilities/FileUtils.o: src/engine/utilities/FileUtils.cpp.o

.PHONY : src/engine/utilities/FileUtils.o

# target to build an object file
src/engine/utilities/FileUtils.cpp.o:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/utilities/FileUtils.cpp.o
.PHONY : src/engine/utilities/FileUtils.cpp.o

src/engine/utilities/FileUtils.i: src/engine/utilities/FileUtils.cpp.i

.PHONY : src/engine/utilities/FileUtils.i

# target to preprocess a source file
src/engine/utilities/FileUtils.cpp.i:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/utilities/FileUtils.cpp.i
.PHONY : src/engine/utilities/FileUtils.cpp.i

src/engine/utilities/FileUtils.s: src/engine/utilities/FileUtils.cpp.s

.PHONY : src/engine/utilities/FileUtils.s

# target to generate assembly for a file
src/engine/utilities/FileUtils.cpp.s:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/utilities/FileUtils.cpp.s
.PHONY : src/engine/utilities/FileUtils.cpp.s

src/engine/utilities/Logger.o: src/engine/utilities/Logger.cpp.o

.PHONY : src/engine/utilities/Logger.o

# target to build an object file
src/engine/utilities/Logger.cpp.o:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/utilities/Logger.cpp.o
.PHONY : src/engine/utilities/Logger.cpp.o

src/engine/utilities/Logger.i: src/engine/utilities/Logger.cpp.i

.PHONY : src/engine/utilities/Logger.i

# target to preprocess a source file
src/engine/utilities/Logger.cpp.i:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/utilities/Logger.cpp.i
.PHONY : src/engine/utilities/Logger.cpp.i

src/engine/utilities/Logger.s: src/engine/utilities/Logger.cpp.s

.PHONY : src/engine/utilities/Logger.s

# target to generate assembly for a file
src/engine/utilities/Logger.cpp.s:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/utilities/Logger.cpp.s
.PHONY : src/engine/utilities/Logger.cpp.s

src/engine/utilities/StringUtils.o: src/engine/utilities/StringUtils.cpp.o

.PHONY : src/engine/utilities/StringUtils.o

# target to build an object file
src/engine/utilities/StringUtils.cpp.o:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/utilities/StringUtils.cpp.o
.PHONY : src/engine/utilities/StringUtils.cpp.o

src/engine/utilities/StringUtils.i: src/engine/utilities/StringUtils.cpp.i

.PHONY : src/engine/utilities/StringUtils.i

# target to preprocess a source file
src/engine/utilities/StringUtils.cpp.i:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/utilities/StringUtils.cpp.i
.PHONY : src/engine/utilities/StringUtils.cpp.i

src/engine/utilities/StringUtils.s: src/engine/utilities/StringUtils.cpp.s

.PHONY : src/engine/utilities/StringUtils.s

# target to generate assembly for a file
src/engine/utilities/StringUtils.cpp.s:
	$(MAKE) -f CMakeFiles/MurderEngine.dir/build.make CMakeFiles/MurderEngine.dir/src/engine/utilities/StringUtils.cpp.s
.PHONY : src/engine/utilities/StringUtils.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... MurderEngine"
	@echo "... src/Main.o"
	@echo "... src/Main.i"
	@echo "... src/Main.s"
	@echo "... src/engine/EngineManager.o"
	@echo "... src/engine/EngineManager.i"
	@echo "... src/engine/EngineManager.s"
	@echo "... src/engine/MurderEngine.o"
	@echo "... src/engine/MurderEngine.i"
	@echo "... src/engine/MurderEngine.s"
	@echo "... src/engine/loaders/ImageReader.o"
	@echo "... src/engine/loaders/ImageReader.i"
	@echo "... src/engine/loaders/ImageReader.s"
	@echo "... src/engine/loaders/mesh_loader.o"
	@echo "... src/engine/loaders/mesh_loader.i"
	@echo "... src/engine/loaders/mesh_loader.s"
	@echo "... src/engine/loaders/parsers/collada_parser.o"
	@echo "... src/engine/loaders/parsers/collada_parser.i"
	@echo "... src/engine/loaders/parsers/collada_parser.s"
	@echo "... src/engine/math/maths.o"
	@echo "... src/engine/math/maths.i"
	@echo "... src/engine/math/maths.s"
	@echo "... src/engine/math/vectors.o"
	@echo "... src/engine/math/vectors.i"
	@echo "... src/engine/math/vectors.s"
	@echo "... src/engine/renderer/OpenGLApi.o"
	@echo "... src/engine/renderer/OpenGLApi.i"
	@echo "... src/engine/renderer/OpenGLApi.s"
	@echo "... src/engine/scene/scene.o"
	@echo "... src/engine/scene/scene.i"
	@echo "... src/engine/scene/scene.s"
	@echo "... src/engine/utilities/ArrayUtils.o"
	@echo "... src/engine/utilities/ArrayUtils.i"
	@echo "... src/engine/utilities/ArrayUtils.s"
	@echo "... src/engine/utilities/FileUtils.o"
	@echo "... src/engine/utilities/FileUtils.i"
	@echo "... src/engine/utilities/FileUtils.s"
	@echo "... src/engine/utilities/Logger.o"
	@echo "... src/engine/utilities/Logger.i"
	@echo "... src/engine/utilities/Logger.s"
	@echo "... src/engine/utilities/StringUtils.o"
	@echo "... src/engine/utilities/StringUtils.i"
	@echo "... src/engine/utilities/StringUtils.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

