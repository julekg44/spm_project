# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/spm_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/spm_project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/progetto.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/progetto.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/progetto.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/progetto.dir/flags.make

CMakeFiles/progetto.dir/main_ff.cpp.o: CMakeFiles/progetto.dir/flags.make
CMakeFiles/progetto.dir/main_ff.cpp.o: ../main_ff.cpp
CMakeFiles/progetto.dir/main_ff.cpp.o: CMakeFiles/progetto.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/spm_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/progetto.dir/main_ff.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/progetto.dir/main_ff.cpp.o -MF CMakeFiles/progetto.dir/main_ff.cpp.o.d -o CMakeFiles/progetto.dir/main_ff.cpp.o -c /tmp/spm_project/main_ff.cpp

CMakeFiles/progetto.dir/main_ff.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/progetto.dir/main_ff.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/spm_project/main_ff.cpp > CMakeFiles/progetto.dir/main_ff.cpp.i

CMakeFiles/progetto.dir/main_ff.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/progetto.dir/main_ff.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/spm_project/main_ff.cpp -o CMakeFiles/progetto.dir/main_ff.cpp.s

CMakeFiles/progetto.dir/util.cpp.o: CMakeFiles/progetto.dir/flags.make
CMakeFiles/progetto.dir/util.cpp.o: ../util.cpp
CMakeFiles/progetto.dir/util.cpp.o: CMakeFiles/progetto.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/spm_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/progetto.dir/util.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/progetto.dir/util.cpp.o -MF CMakeFiles/progetto.dir/util.cpp.o.d -o CMakeFiles/progetto.dir/util.cpp.o -c /tmp/spm_project/util.cpp

CMakeFiles/progetto.dir/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/progetto.dir/util.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/spm_project/util.cpp > CMakeFiles/progetto.dir/util.cpp.i

CMakeFiles/progetto.dir/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/progetto.dir/util.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/spm_project/util.cpp -o CMakeFiles/progetto.dir/util.cpp.s

# Object files for target progetto
progetto_OBJECTS = \
"CMakeFiles/progetto.dir/main_ff.cpp.o" \
"CMakeFiles/progetto.dir/util.cpp.o"

# External object files for target progetto
progetto_EXTERNAL_OBJECTS =

progetto: CMakeFiles/progetto.dir/main_ff.cpp.o
progetto: CMakeFiles/progetto.dir/util.cpp.o
progetto: CMakeFiles/progetto.dir/build.make
progetto: CMakeFiles/progetto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/spm_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable progetto"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/progetto.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/progetto.dir/build: progetto
.PHONY : CMakeFiles/progetto.dir/build

CMakeFiles/progetto.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/progetto.dir/cmake_clean.cmake
.PHONY : CMakeFiles/progetto.dir/clean

CMakeFiles/progetto.dir/depend:
	cd /tmp/spm_project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/spm_project /tmp/spm_project /tmp/spm_project/cmake-build-debug /tmp/spm_project/cmake-build-debug /tmp/spm_project/cmake-build-debug/CMakeFiles/progetto.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/progetto.dir/depend

