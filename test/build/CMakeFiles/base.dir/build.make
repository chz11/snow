# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/nono/Desktop/snow/base/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nono/Desktop/snow/base/test/build

# Include any dependencies generated for this target.
include CMakeFiles/base.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/base.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/base.dir/flags.make

CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.o: CMakeFiles/base.dir/flags.make
CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.o: /home/nono/Desktop/snow/base/log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nono/Desktop/snow/base/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.o -c /home/nono/Desktop/snow/base/log.cpp

CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nono/Desktop/snow/base/log.cpp > CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.i

CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nono/Desktop/snow/base/log.cpp -o CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.s

CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.o.requires:

.PHONY : CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.o.requires

CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.o.provides: CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.o.requires
	$(MAKE) -f CMakeFiles/base.dir/build.make CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.o.provides.build
.PHONY : CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.o.provides

CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.o.provides.build: CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.o


# Object files for target base
base_OBJECTS = \
"CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.o"

# External object files for target base
base_EXTERNAL_OBJECTS =

$(PROJECT_SOURCE_DIR)/lib/libbase.so: CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.o
$(PROJECT_SOURCE_DIR)/lib/libbase.so: CMakeFiles/base.dir/build.make
$(PROJECT_SOURCE_DIR)/lib/libbase.so: CMakeFiles/base.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nono/Desktop/snow/base/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library \$$(PROJECT_SOURCE_DIR)/lib/libbase.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/base.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/base.dir/build: $(PROJECT_SOURCE_DIR)/lib/libbase.so

.PHONY : CMakeFiles/base.dir/build

CMakeFiles/base.dir/requires: CMakeFiles/base.dir/home/nono/Desktop/snow/base/log.o.requires

.PHONY : CMakeFiles/base.dir/requires

CMakeFiles/base.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/base.dir/cmake_clean.cmake
.PHONY : CMakeFiles/base.dir/clean

CMakeFiles/base.dir/depend:
	cd /home/nono/Desktop/snow/base/test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nono/Desktop/snow/base/test /home/nono/Desktop/snow/base/test /home/nono/Desktop/snow/base/test/build /home/nono/Desktop/snow/base/test/build /home/nono/Desktop/snow/base/test/build/CMakeFiles/base.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/base.dir/depend

