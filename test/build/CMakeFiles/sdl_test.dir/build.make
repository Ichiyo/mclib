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
CMAKE_SOURCE_DIR = /home/manh/Documents/mclib/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/manh/Documents/mclib/test/build

# Include any dependencies generated for this target.
include CMakeFiles/sdl_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sdl_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sdl_test.dir/flags.make

temp:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/manh/Documents/mclib/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating temp"
	cd /home/manh/Documents/mclib && mkdir -p build
	cd /home/manh/Documents/mclib && /usr/bin/cmake -Bbuild -H.
	cd /home/manh/Documents/mclib && make -C build

CMakeFiles/sdl_test.dir/sdl_test.c.o: CMakeFiles/sdl_test.dir/flags.make
CMakeFiles/sdl_test.dir/sdl_test.c.o: ../sdl_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/manh/Documents/mclib/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/sdl_test.dir/sdl_test.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sdl_test.dir/sdl_test.c.o   -c /home/manh/Documents/mclib/test/sdl_test.c

CMakeFiles/sdl_test.dir/sdl_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sdl_test.dir/sdl_test.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/manh/Documents/mclib/test/sdl_test.c > CMakeFiles/sdl_test.dir/sdl_test.c.i

CMakeFiles/sdl_test.dir/sdl_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sdl_test.dir/sdl_test.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/manh/Documents/mclib/test/sdl_test.c -o CMakeFiles/sdl_test.dir/sdl_test.c.s

CMakeFiles/sdl_test.dir/sdl_test.c.o.requires:

.PHONY : CMakeFiles/sdl_test.dir/sdl_test.c.o.requires

CMakeFiles/sdl_test.dir/sdl_test.c.o.provides: CMakeFiles/sdl_test.dir/sdl_test.c.o.requires
	$(MAKE) -f CMakeFiles/sdl_test.dir/build.make CMakeFiles/sdl_test.dir/sdl_test.c.o.provides.build
.PHONY : CMakeFiles/sdl_test.dir/sdl_test.c.o.provides

CMakeFiles/sdl_test.dir/sdl_test.c.o.provides.build: CMakeFiles/sdl_test.dir/sdl_test.c.o


# Object files for target sdl_test
sdl_test_OBJECTS = \
"CMakeFiles/sdl_test.dir/sdl_test.c.o"

# External object files for target sdl_test
sdl_test_EXTERNAL_OBJECTS =

sdl_test: CMakeFiles/sdl_test.dir/sdl_test.c.o
sdl_test: CMakeFiles/sdl_test.dir/build.make
sdl_test: ../../build/libclibraries.a
sdl_test: CMakeFiles/sdl_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/manh/Documents/mclib/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable sdl_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sdl_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sdl_test.dir/build: sdl_test

.PHONY : CMakeFiles/sdl_test.dir/build

CMakeFiles/sdl_test.dir/requires: CMakeFiles/sdl_test.dir/sdl_test.c.o.requires

.PHONY : CMakeFiles/sdl_test.dir/requires

CMakeFiles/sdl_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sdl_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sdl_test.dir/clean

CMakeFiles/sdl_test.dir/depend: temp
	cd /home/manh/Documents/mclib/test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/manh/Documents/mclib/test /home/manh/Documents/mclib/test /home/manh/Documents/mclib/test/build /home/manh/Documents/mclib/test/build /home/manh/Documents/mclib/test/build/CMakeFiles/sdl_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sdl_test.dir/depend

