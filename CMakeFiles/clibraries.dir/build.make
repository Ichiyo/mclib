# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/manh/Documents/mclib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/manh/Documents/mclib

# Include any dependencies generated for this target.
include CMakeFiles/clibraries.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/clibraries.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/clibraries.dir/flags.make

CMakeFiles/clibraries.dir/src/texture.c.o: CMakeFiles/clibraries.dir/flags.make
CMakeFiles/clibraries.dir/src/texture.c.o: src/texture.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manh/Documents/mclib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/clibraries.dir/src/texture.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/clibraries.dir/src/texture.c.o   -c /home/manh/Documents/mclib/src/texture.c

CMakeFiles/clibraries.dir/src/texture.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clibraries.dir/src/texture.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/manh/Documents/mclib/src/texture.c > CMakeFiles/clibraries.dir/src/texture.c.i

CMakeFiles/clibraries.dir/src/texture.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clibraries.dir/src/texture.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/manh/Documents/mclib/src/texture.c -o CMakeFiles/clibraries.dir/src/texture.c.s

CMakeFiles/clibraries.dir/src/texture.c.o.requires:

.PHONY : CMakeFiles/clibraries.dir/src/texture.c.o.requires

CMakeFiles/clibraries.dir/src/texture.c.o.provides: CMakeFiles/clibraries.dir/src/texture.c.o.requires
	$(MAKE) -f CMakeFiles/clibraries.dir/build.make CMakeFiles/clibraries.dir/src/texture.c.o.provides.build
.PHONY : CMakeFiles/clibraries.dir/src/texture.c.o.provides

CMakeFiles/clibraries.dir/src/texture.c.o.provides.build: CMakeFiles/clibraries.dir/src/texture.c.o


CMakeFiles/clibraries.dir/src/data.c.o: CMakeFiles/clibraries.dir/flags.make
CMakeFiles/clibraries.dir/src/data.c.o: src/data.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manh/Documents/mclib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/clibraries.dir/src/data.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/clibraries.dir/src/data.c.o   -c /home/manh/Documents/mclib/src/data.c

CMakeFiles/clibraries.dir/src/data.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clibraries.dir/src/data.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/manh/Documents/mclib/src/data.c > CMakeFiles/clibraries.dir/src/data.c.i

CMakeFiles/clibraries.dir/src/data.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clibraries.dir/src/data.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/manh/Documents/mclib/src/data.c -o CMakeFiles/clibraries.dir/src/data.c.s

CMakeFiles/clibraries.dir/src/data.c.o.requires:

.PHONY : CMakeFiles/clibraries.dir/src/data.c.o.requires

CMakeFiles/clibraries.dir/src/data.c.o.provides: CMakeFiles/clibraries.dir/src/data.c.o.requires
	$(MAKE) -f CMakeFiles/clibraries.dir/build.make CMakeFiles/clibraries.dir/src/data.c.o.provides.build
.PHONY : CMakeFiles/clibraries.dir/src/data.c.o.provides

CMakeFiles/clibraries.dir/src/data.c.o.provides.build: CMakeFiles/clibraries.dir/src/data.c.o


CMakeFiles/clibraries.dir/src/map.c.o: CMakeFiles/clibraries.dir/flags.make
CMakeFiles/clibraries.dir/src/map.c.o: src/map.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manh/Documents/mclib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/clibraries.dir/src/map.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/clibraries.dir/src/map.c.o   -c /home/manh/Documents/mclib/src/map.c

CMakeFiles/clibraries.dir/src/map.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clibraries.dir/src/map.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/manh/Documents/mclib/src/map.c > CMakeFiles/clibraries.dir/src/map.c.i

CMakeFiles/clibraries.dir/src/map.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clibraries.dir/src/map.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/manh/Documents/mclib/src/map.c -o CMakeFiles/clibraries.dir/src/map.c.s

CMakeFiles/clibraries.dir/src/map.c.o.requires:

.PHONY : CMakeFiles/clibraries.dir/src/map.c.o.requires

CMakeFiles/clibraries.dir/src/map.c.o.provides: CMakeFiles/clibraries.dir/src/map.c.o.requires
	$(MAKE) -f CMakeFiles/clibraries.dir/build.make CMakeFiles/clibraries.dir/src/map.c.o.provides.build
.PHONY : CMakeFiles/clibraries.dir/src/map.c.o.provides

CMakeFiles/clibraries.dir/src/map.c.o.provides.build: CMakeFiles/clibraries.dir/src/map.c.o


CMakeFiles/clibraries.dir/src/string.c.o: CMakeFiles/clibraries.dir/flags.make
CMakeFiles/clibraries.dir/src/string.c.o: src/string.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manh/Documents/mclib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/clibraries.dir/src/string.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/clibraries.dir/src/string.c.o   -c /home/manh/Documents/mclib/src/string.c

CMakeFiles/clibraries.dir/src/string.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clibraries.dir/src/string.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/manh/Documents/mclib/src/string.c > CMakeFiles/clibraries.dir/src/string.c.i

CMakeFiles/clibraries.dir/src/string.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clibraries.dir/src/string.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/manh/Documents/mclib/src/string.c -o CMakeFiles/clibraries.dir/src/string.c.s

CMakeFiles/clibraries.dir/src/string.c.o.requires:

.PHONY : CMakeFiles/clibraries.dir/src/string.c.o.requires

CMakeFiles/clibraries.dir/src/string.c.o.provides: CMakeFiles/clibraries.dir/src/string.c.o.requires
	$(MAKE) -f CMakeFiles/clibraries.dir/build.make CMakeFiles/clibraries.dir/src/string.c.o.provides.build
.PHONY : CMakeFiles/clibraries.dir/src/string.c.o.provides

CMakeFiles/clibraries.dir/src/string.c.o.provides.build: CMakeFiles/clibraries.dir/src/string.c.o


CMakeFiles/clibraries.dir/src/serialize.c.o: CMakeFiles/clibraries.dir/flags.make
CMakeFiles/clibraries.dir/src/serialize.c.o: src/serialize.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manh/Documents/mclib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/clibraries.dir/src/serialize.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/clibraries.dir/src/serialize.c.o   -c /home/manh/Documents/mclib/src/serialize.c

CMakeFiles/clibraries.dir/src/serialize.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clibraries.dir/src/serialize.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/manh/Documents/mclib/src/serialize.c > CMakeFiles/clibraries.dir/src/serialize.c.i

CMakeFiles/clibraries.dir/src/serialize.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clibraries.dir/src/serialize.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/manh/Documents/mclib/src/serialize.c -o CMakeFiles/clibraries.dir/src/serialize.c.s

CMakeFiles/clibraries.dir/src/serialize.c.o.requires:

.PHONY : CMakeFiles/clibraries.dir/src/serialize.c.o.requires

CMakeFiles/clibraries.dir/src/serialize.c.o.provides: CMakeFiles/clibraries.dir/src/serialize.c.o.requires
	$(MAKE) -f CMakeFiles/clibraries.dir/build.make CMakeFiles/clibraries.dir/src/serialize.c.o.provides.build
.PHONY : CMakeFiles/clibraries.dir/src/serialize.c.o.provides

CMakeFiles/clibraries.dir/src/serialize.c.o.provides.build: CMakeFiles/clibraries.dir/src/serialize.c.o


CMakeFiles/clibraries.dir/src/node.c.o: CMakeFiles/clibraries.dir/flags.make
CMakeFiles/clibraries.dir/src/node.c.o: src/node.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manh/Documents/mclib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/clibraries.dir/src/node.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/clibraries.dir/src/node.c.o   -c /home/manh/Documents/mclib/src/node.c

CMakeFiles/clibraries.dir/src/node.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clibraries.dir/src/node.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/manh/Documents/mclib/src/node.c > CMakeFiles/clibraries.dir/src/node.c.i

CMakeFiles/clibraries.dir/src/node.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clibraries.dir/src/node.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/manh/Documents/mclib/src/node.c -o CMakeFiles/clibraries.dir/src/node.c.s

CMakeFiles/clibraries.dir/src/node.c.o.requires:

.PHONY : CMakeFiles/clibraries.dir/src/node.c.o.requires

CMakeFiles/clibraries.dir/src/node.c.o.provides: CMakeFiles/clibraries.dir/src/node.c.o.requires
	$(MAKE) -f CMakeFiles/clibraries.dir/build.make CMakeFiles/clibraries.dir/src/node.c.o.provides.build
.PHONY : CMakeFiles/clibraries.dir/src/node.c.o.provides

CMakeFiles/clibraries.dir/src/node.c.o.provides.build: CMakeFiles/clibraries.dir/src/node.c.o


CMakeFiles/clibraries.dir/src/shader.c.o: CMakeFiles/clibraries.dir/flags.make
CMakeFiles/clibraries.dir/src/shader.c.o: src/shader.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manh/Documents/mclib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/clibraries.dir/src/shader.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/clibraries.dir/src/shader.c.o   -c /home/manh/Documents/mclib/src/shader.c

CMakeFiles/clibraries.dir/src/shader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clibraries.dir/src/shader.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/manh/Documents/mclib/src/shader.c > CMakeFiles/clibraries.dir/src/shader.c.i

CMakeFiles/clibraries.dir/src/shader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clibraries.dir/src/shader.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/manh/Documents/mclib/src/shader.c -o CMakeFiles/clibraries.dir/src/shader.c.s

CMakeFiles/clibraries.dir/src/shader.c.o.requires:

.PHONY : CMakeFiles/clibraries.dir/src/shader.c.o.requires

CMakeFiles/clibraries.dir/src/shader.c.o.provides: CMakeFiles/clibraries.dir/src/shader.c.o.requires
	$(MAKE) -f CMakeFiles/clibraries.dir/build.make CMakeFiles/clibraries.dir/src/shader.c.o.provides.build
.PHONY : CMakeFiles/clibraries.dir/src/shader.c.o.provides

CMakeFiles/clibraries.dir/src/shader.c.o.provides.build: CMakeFiles/clibraries.dir/src/shader.c.o


CMakeFiles/clibraries.dir/src/utils.c.o: CMakeFiles/clibraries.dir/flags.make
CMakeFiles/clibraries.dir/src/utils.c.o: src/utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manh/Documents/mclib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/clibraries.dir/src/utils.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/clibraries.dir/src/utils.c.o   -c /home/manh/Documents/mclib/src/utils.c

CMakeFiles/clibraries.dir/src/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clibraries.dir/src/utils.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/manh/Documents/mclib/src/utils.c > CMakeFiles/clibraries.dir/src/utils.c.i

CMakeFiles/clibraries.dir/src/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clibraries.dir/src/utils.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/manh/Documents/mclib/src/utils.c -o CMakeFiles/clibraries.dir/src/utils.c.s

CMakeFiles/clibraries.dir/src/utils.c.o.requires:

.PHONY : CMakeFiles/clibraries.dir/src/utils.c.o.requires

CMakeFiles/clibraries.dir/src/utils.c.o.provides: CMakeFiles/clibraries.dir/src/utils.c.o.requires
	$(MAKE) -f CMakeFiles/clibraries.dir/build.make CMakeFiles/clibraries.dir/src/utils.c.o.provides.build
.PHONY : CMakeFiles/clibraries.dir/src/utils.c.o.provides

CMakeFiles/clibraries.dir/src/utils.c.o.provides.build: CMakeFiles/clibraries.dir/src/utils.c.o


CMakeFiles/clibraries.dir/src/math.c.o: CMakeFiles/clibraries.dir/flags.make
CMakeFiles/clibraries.dir/src/math.c.o: src/math.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manh/Documents/mclib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/clibraries.dir/src/math.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/clibraries.dir/src/math.c.o   -c /home/manh/Documents/mclib/src/math.c

CMakeFiles/clibraries.dir/src/math.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clibraries.dir/src/math.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/manh/Documents/mclib/src/math.c > CMakeFiles/clibraries.dir/src/math.c.i

CMakeFiles/clibraries.dir/src/math.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clibraries.dir/src/math.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/manh/Documents/mclib/src/math.c -o CMakeFiles/clibraries.dir/src/math.c.s

CMakeFiles/clibraries.dir/src/math.c.o.requires:

.PHONY : CMakeFiles/clibraries.dir/src/math.c.o.requires

CMakeFiles/clibraries.dir/src/math.c.o.provides: CMakeFiles/clibraries.dir/src/math.c.o.requires
	$(MAKE) -f CMakeFiles/clibraries.dir/build.make CMakeFiles/clibraries.dir/src/math.c.o.provides.build
.PHONY : CMakeFiles/clibraries.dir/src/math.c.o.provides

CMakeFiles/clibraries.dir/src/math.c.o.provides.build: CMakeFiles/clibraries.dir/src/math.c.o


CMakeFiles/clibraries.dir/src/primitive.c.o: CMakeFiles/clibraries.dir/flags.make
CMakeFiles/clibraries.dir/src/primitive.c.o: src/primitive.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manh/Documents/mclib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/clibraries.dir/src/primitive.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/clibraries.dir/src/primitive.c.o   -c /home/manh/Documents/mclib/src/primitive.c

CMakeFiles/clibraries.dir/src/primitive.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clibraries.dir/src/primitive.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/manh/Documents/mclib/src/primitive.c > CMakeFiles/clibraries.dir/src/primitive.c.i

CMakeFiles/clibraries.dir/src/primitive.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clibraries.dir/src/primitive.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/manh/Documents/mclib/src/primitive.c -o CMakeFiles/clibraries.dir/src/primitive.c.s

CMakeFiles/clibraries.dir/src/primitive.c.o.requires:

.PHONY : CMakeFiles/clibraries.dir/src/primitive.c.o.requires

CMakeFiles/clibraries.dir/src/primitive.c.o.provides: CMakeFiles/clibraries.dir/src/primitive.c.o.requires
	$(MAKE) -f CMakeFiles/clibraries.dir/build.make CMakeFiles/clibraries.dir/src/primitive.c.o.provides.build
.PHONY : CMakeFiles/clibraries.dir/src/primitive.c.o.provides

CMakeFiles/clibraries.dir/src/primitive.c.o.provides.build: CMakeFiles/clibraries.dir/src/primitive.c.o


CMakeFiles/clibraries.dir/src/image.c.o: CMakeFiles/clibraries.dir/flags.make
CMakeFiles/clibraries.dir/src/image.c.o: src/image.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manh/Documents/mclib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/clibraries.dir/src/image.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/clibraries.dir/src/image.c.o   -c /home/manh/Documents/mclib/src/image.c

CMakeFiles/clibraries.dir/src/image.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clibraries.dir/src/image.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/manh/Documents/mclib/src/image.c > CMakeFiles/clibraries.dir/src/image.c.i

CMakeFiles/clibraries.dir/src/image.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clibraries.dir/src/image.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/manh/Documents/mclib/src/image.c -o CMakeFiles/clibraries.dir/src/image.c.s

CMakeFiles/clibraries.dir/src/image.c.o.requires:

.PHONY : CMakeFiles/clibraries.dir/src/image.c.o.requires

CMakeFiles/clibraries.dir/src/image.c.o.provides: CMakeFiles/clibraries.dir/src/image.c.o.requires
	$(MAKE) -f CMakeFiles/clibraries.dir/build.make CMakeFiles/clibraries.dir/src/image.c.o.provides.build
.PHONY : CMakeFiles/clibraries.dir/src/image.c.o.provides

CMakeFiles/clibraries.dir/src/image.c.o.provides.build: CMakeFiles/clibraries.dir/src/image.c.o


CMakeFiles/clibraries.dir/src/base.c.o: CMakeFiles/clibraries.dir/flags.make
CMakeFiles/clibraries.dir/src/base.c.o: src/base.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manh/Documents/mclib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/clibraries.dir/src/base.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/clibraries.dir/src/base.c.o   -c /home/manh/Documents/mclib/src/base.c

CMakeFiles/clibraries.dir/src/base.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clibraries.dir/src/base.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/manh/Documents/mclib/src/base.c > CMakeFiles/clibraries.dir/src/base.c.i

CMakeFiles/clibraries.dir/src/base.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clibraries.dir/src/base.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/manh/Documents/mclib/src/base.c -o CMakeFiles/clibraries.dir/src/base.c.s

CMakeFiles/clibraries.dir/src/base.c.o.requires:

.PHONY : CMakeFiles/clibraries.dir/src/base.c.o.requires

CMakeFiles/clibraries.dir/src/base.c.o.provides: CMakeFiles/clibraries.dir/src/base.c.o.requires
	$(MAKE) -f CMakeFiles/clibraries.dir/build.make CMakeFiles/clibraries.dir/src/base.c.o.provides.build
.PHONY : CMakeFiles/clibraries.dir/src/base.c.o.provides

CMakeFiles/clibraries.dir/src/base.c.o.provides.build: CMakeFiles/clibraries.dir/src/base.c.o


CMakeFiles/clibraries.dir/src/list.c.o: CMakeFiles/clibraries.dir/flags.make
CMakeFiles/clibraries.dir/src/list.c.o: src/list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manh/Documents/mclib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/clibraries.dir/src/list.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/clibraries.dir/src/list.c.o   -c /home/manh/Documents/mclib/src/list.c

CMakeFiles/clibraries.dir/src/list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/clibraries.dir/src/list.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/manh/Documents/mclib/src/list.c > CMakeFiles/clibraries.dir/src/list.c.i

CMakeFiles/clibraries.dir/src/list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/clibraries.dir/src/list.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/manh/Documents/mclib/src/list.c -o CMakeFiles/clibraries.dir/src/list.c.s

CMakeFiles/clibraries.dir/src/list.c.o.requires:

.PHONY : CMakeFiles/clibraries.dir/src/list.c.o.requires

CMakeFiles/clibraries.dir/src/list.c.o.provides: CMakeFiles/clibraries.dir/src/list.c.o.requires
	$(MAKE) -f CMakeFiles/clibraries.dir/build.make CMakeFiles/clibraries.dir/src/list.c.o.provides.build
.PHONY : CMakeFiles/clibraries.dir/src/list.c.o.provides

CMakeFiles/clibraries.dir/src/list.c.o.provides.build: CMakeFiles/clibraries.dir/src/list.c.o


# Object files for target clibraries
clibraries_OBJECTS = \
"CMakeFiles/clibraries.dir/src/texture.c.o" \
"CMakeFiles/clibraries.dir/src/data.c.o" \
"CMakeFiles/clibraries.dir/src/map.c.o" \
"CMakeFiles/clibraries.dir/src/string.c.o" \
"CMakeFiles/clibraries.dir/src/serialize.c.o" \
"CMakeFiles/clibraries.dir/src/node.c.o" \
"CMakeFiles/clibraries.dir/src/shader.c.o" \
"CMakeFiles/clibraries.dir/src/utils.c.o" \
"CMakeFiles/clibraries.dir/src/math.c.o" \
"CMakeFiles/clibraries.dir/src/primitive.c.o" \
"CMakeFiles/clibraries.dir/src/image.c.o" \
"CMakeFiles/clibraries.dir/src/base.c.o" \
"CMakeFiles/clibraries.dir/src/list.c.o"

# External object files for target clibraries
clibraries_EXTERNAL_OBJECTS =

libclibraries.so: CMakeFiles/clibraries.dir/src/texture.c.o
libclibraries.so: CMakeFiles/clibraries.dir/src/data.c.o
libclibraries.so: CMakeFiles/clibraries.dir/src/map.c.o
libclibraries.so: CMakeFiles/clibraries.dir/src/string.c.o
libclibraries.so: CMakeFiles/clibraries.dir/src/serialize.c.o
libclibraries.so: CMakeFiles/clibraries.dir/src/node.c.o
libclibraries.so: CMakeFiles/clibraries.dir/src/shader.c.o
libclibraries.so: CMakeFiles/clibraries.dir/src/utils.c.o
libclibraries.so: CMakeFiles/clibraries.dir/src/math.c.o
libclibraries.so: CMakeFiles/clibraries.dir/src/primitive.c.o
libclibraries.so: CMakeFiles/clibraries.dir/src/image.c.o
libclibraries.so: CMakeFiles/clibraries.dir/src/base.c.o
libclibraries.so: CMakeFiles/clibraries.dir/src/list.c.o
libclibraries.so: CMakeFiles/clibraries.dir/build.make
libclibraries.so: CMakeFiles/clibraries.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/manh/Documents/mclib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking C shared library libclibraries.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clibraries.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/clibraries.dir/build: libclibraries.so

.PHONY : CMakeFiles/clibraries.dir/build

CMakeFiles/clibraries.dir/requires: CMakeFiles/clibraries.dir/src/texture.c.o.requires
CMakeFiles/clibraries.dir/requires: CMakeFiles/clibraries.dir/src/data.c.o.requires
CMakeFiles/clibraries.dir/requires: CMakeFiles/clibraries.dir/src/map.c.o.requires
CMakeFiles/clibraries.dir/requires: CMakeFiles/clibraries.dir/src/string.c.o.requires
CMakeFiles/clibraries.dir/requires: CMakeFiles/clibraries.dir/src/serialize.c.o.requires
CMakeFiles/clibraries.dir/requires: CMakeFiles/clibraries.dir/src/node.c.o.requires
CMakeFiles/clibraries.dir/requires: CMakeFiles/clibraries.dir/src/shader.c.o.requires
CMakeFiles/clibraries.dir/requires: CMakeFiles/clibraries.dir/src/utils.c.o.requires
CMakeFiles/clibraries.dir/requires: CMakeFiles/clibraries.dir/src/math.c.o.requires
CMakeFiles/clibraries.dir/requires: CMakeFiles/clibraries.dir/src/primitive.c.o.requires
CMakeFiles/clibraries.dir/requires: CMakeFiles/clibraries.dir/src/image.c.o.requires
CMakeFiles/clibraries.dir/requires: CMakeFiles/clibraries.dir/src/base.c.o.requires
CMakeFiles/clibraries.dir/requires: CMakeFiles/clibraries.dir/src/list.c.o.requires

.PHONY : CMakeFiles/clibraries.dir/requires

CMakeFiles/clibraries.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/clibraries.dir/cmake_clean.cmake
.PHONY : CMakeFiles/clibraries.dir/clean

CMakeFiles/clibraries.dir/depend:
	cd /home/manh/Documents/mclib && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/manh/Documents/mclib /home/manh/Documents/mclib /home/manh/Documents/mclib /home/manh/Documents/mclib /home/manh/Documents/mclib/CMakeFiles/clibraries.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/clibraries.dir/depend

