# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = /home/alaska/GitHub/danya/cpp_with_tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alaska/GitHub/danya/cpp_with_tests

# Include any dependencies generated for this target.
include functions/CMakeFiles/functions.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include functions/CMakeFiles/functions.dir/compiler_depend.make

# Include the progress variables for this target.
include functions/CMakeFiles/functions.dir/progress.make

# Include the compile flags for this target's objects.
include functions/CMakeFiles/functions.dir/flags.make

functions/CMakeFiles/functions.dir/func.cpp.o: functions/CMakeFiles/functions.dir/flags.make
functions/CMakeFiles/functions.dir/func.cpp.o: functions/func.cpp
functions/CMakeFiles/functions.dir/func.cpp.o: functions/CMakeFiles/functions.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/alaska/GitHub/danya/cpp_with_tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object functions/CMakeFiles/functions.dir/func.cpp.o"
	cd /home/alaska/GitHub/danya/cpp_with_tests/functions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT functions/CMakeFiles/functions.dir/func.cpp.o -MF CMakeFiles/functions.dir/func.cpp.o.d -o CMakeFiles/functions.dir/func.cpp.o -c /home/alaska/GitHub/danya/cpp_with_tests/functions/func.cpp

functions/CMakeFiles/functions.dir/func.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/functions.dir/func.cpp.i"
	cd /home/alaska/GitHub/danya/cpp_with_tests/functions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alaska/GitHub/danya/cpp_with_tests/functions/func.cpp > CMakeFiles/functions.dir/func.cpp.i

functions/CMakeFiles/functions.dir/func.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/functions.dir/func.cpp.s"
	cd /home/alaska/GitHub/danya/cpp_with_tests/functions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alaska/GitHub/danya/cpp_with_tests/functions/func.cpp -o CMakeFiles/functions.dir/func.cpp.s

# Object files for target functions
functions_OBJECTS = \
"CMakeFiles/functions.dir/func.cpp.o"

# External object files for target functions
functions_EXTERNAL_OBJECTS =

functions/libfunctions.a: functions/CMakeFiles/functions.dir/func.cpp.o
functions/libfunctions.a: functions/CMakeFiles/functions.dir/build.make
functions/libfunctions.a: functions/CMakeFiles/functions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/alaska/GitHub/danya/cpp_with_tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libfunctions.a"
	cd /home/alaska/GitHub/danya/cpp_with_tests/functions && $(CMAKE_COMMAND) -P CMakeFiles/functions.dir/cmake_clean_target.cmake
	cd /home/alaska/GitHub/danya/cpp_with_tests/functions && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/functions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
functions/CMakeFiles/functions.dir/build: functions/libfunctions.a
.PHONY : functions/CMakeFiles/functions.dir/build

functions/CMakeFiles/functions.dir/clean:
	cd /home/alaska/GitHub/danya/cpp_with_tests/functions && $(CMAKE_COMMAND) -P CMakeFiles/functions.dir/cmake_clean.cmake
.PHONY : functions/CMakeFiles/functions.dir/clean

functions/CMakeFiles/functions.dir/depend:
	cd /home/alaska/GitHub/danya/cpp_with_tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alaska/GitHub/danya/cpp_with_tests /home/alaska/GitHub/danya/cpp_with_tests/functions /home/alaska/GitHub/danya/cpp_with_tests /home/alaska/GitHub/danya/cpp_with_tests/functions /home/alaska/GitHub/danya/cpp_with_tests/functions/CMakeFiles/functions.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : functions/CMakeFiles/functions.dir/depend

