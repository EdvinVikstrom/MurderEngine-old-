# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# Include any dependencies generated for this target.
include src/external/glfw/tests/CMakeFiles/threads.dir/depend.make

# Include the progress variables for this target.
include src/external/glfw/tests/CMakeFiles/threads.dir/progress.make

# Include the compile flags for this target's objects.
include src/external/glfw/tests/CMakeFiles/threads.dir/flags.make

src/external/glfw/tests/CMakeFiles/threads.dir/threads.c.o: src/external/glfw/tests/CMakeFiles/threads.dir/flags.make
src/external/glfw/tests/CMakeFiles/threads.dir/threads.c.o: src/external/glfw/tests/threads.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/edvinskomputa/Dokument/OnePunchEngine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/external/glfw/tests/CMakeFiles/threads.dir/threads.c.o"
	cd /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/threads.dir/threads.c.o   -c /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests/threads.c

src/external/glfw/tests/CMakeFiles/threads.dir/threads.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/threads.dir/threads.c.i"
	cd /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests/threads.c > CMakeFiles/threads.dir/threads.c.i

src/external/glfw/tests/CMakeFiles/threads.dir/threads.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/threads.dir/threads.c.s"
	cd /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests/threads.c -o CMakeFiles/threads.dir/threads.c.s

src/external/glfw/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o: src/external/glfw/tests/CMakeFiles/threads.dir/flags.make
src/external/glfw/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o: src/external/glfw/deps/tinycthread.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/edvinskomputa/Dokument/OnePunchEngine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/external/glfw/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o"
	cd /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/threads.dir/__/deps/tinycthread.c.o   -c /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/deps/tinycthread.c

src/external/glfw/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/threads.dir/__/deps/tinycthread.c.i"
	cd /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/deps/tinycthread.c > CMakeFiles/threads.dir/__/deps/tinycthread.c.i

src/external/glfw/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/threads.dir/__/deps/tinycthread.c.s"
	cd /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/deps/tinycthread.c -o CMakeFiles/threads.dir/__/deps/tinycthread.c.s

src/external/glfw/tests/CMakeFiles/threads.dir/__/deps/glad_gl.c.o: src/external/glfw/tests/CMakeFiles/threads.dir/flags.make
src/external/glfw/tests/CMakeFiles/threads.dir/__/deps/glad_gl.c.o: src/external/glfw/deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/edvinskomputa/Dokument/OnePunchEngine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/external/glfw/tests/CMakeFiles/threads.dir/__/deps/glad_gl.c.o"
	cd /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/threads.dir/__/deps/glad_gl.c.o   -c /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/deps/glad_gl.c

src/external/glfw/tests/CMakeFiles/threads.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/threads.dir/__/deps/glad_gl.c.i"
	cd /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/deps/glad_gl.c > CMakeFiles/threads.dir/__/deps/glad_gl.c.i

src/external/glfw/tests/CMakeFiles/threads.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/threads.dir/__/deps/glad_gl.c.s"
	cd /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/deps/glad_gl.c -o CMakeFiles/threads.dir/__/deps/glad_gl.c.s

# Object files for target threads
threads_OBJECTS = \
"CMakeFiles/threads.dir/threads.c.o" \
"CMakeFiles/threads.dir/__/deps/tinycthread.c.o" \
"CMakeFiles/threads.dir/__/deps/glad_gl.c.o"

# External object files for target threads
threads_EXTERNAL_OBJECTS =

src/external/glfw/tests/threads: src/external/glfw/tests/CMakeFiles/threads.dir/threads.c.o
src/external/glfw/tests/threads: src/external/glfw/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o
src/external/glfw/tests/threads: src/external/glfw/tests/CMakeFiles/threads.dir/__/deps/glad_gl.c.o
src/external/glfw/tests/threads: src/external/glfw/tests/CMakeFiles/threads.dir/build.make
src/external/glfw/tests/threads: src/external/glfw/src/libglfw3.a
src/external/glfw/tests/threads: /usr/lib/libm.so
src/external/glfw/tests/threads: /usr/lib/librt.so
src/external/glfw/tests/threads: /usr/lib/libX11.so
src/external/glfw/tests/threads: src/external/glfw/tests/CMakeFiles/threads.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/edvinskomputa/Dokument/OnePunchEngine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable threads"
	cd /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threads.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/external/glfw/tests/CMakeFiles/threads.dir/build: src/external/glfw/tests/threads

.PHONY : src/external/glfw/tests/CMakeFiles/threads.dir/build

src/external/glfw/tests/CMakeFiles/threads.dir/clean:
	cd /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/threads.dir/cmake_clean.cmake
.PHONY : src/external/glfw/tests/CMakeFiles/threads.dir/clean

src/external/glfw/tests/CMakeFiles/threads.dir/depend:
	cd /home/edvinskomputa/Dokument/OnePunchEngine && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/edvinskomputa/Dokument/OnePunchEngine /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests /home/edvinskomputa/Dokument/OnePunchEngine /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests /home/edvinskomputa/Dokument/OnePunchEngine/src/external/glfw/tests/CMakeFiles/threads.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/external/glfw/tests/CMakeFiles/threads.dir/depend
