# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/new_danya_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/new_danya_cpp/build

# Include any dependencies generated for this target.
include saves/CMakeFiles/saves.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include saves/CMakeFiles/saves.dir/compiler_depend.make

# Include the progress variables for this target.
include saves/CMakeFiles/saves.dir/progress.make

# Include the compile flags for this target's objects.
include saves/CMakeFiles/saves.dir/flags.make

saves/CMakeFiles/saves.dir/saves.cpp.obj: saves/CMakeFiles/saves.dir/flags.make
saves/CMakeFiles/saves.dir/saves.cpp.obj: saves/CMakeFiles/saves.dir/includes_CXX.rsp
saves/CMakeFiles/saves.dir/saves.cpp.obj: C:/new_danya_cpp/saves/saves.cpp
saves/CMakeFiles/saves.dir/saves.cpp.obj: saves/CMakeFiles/saves.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:/new_danya_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object saves/CMakeFiles/saves.dir/saves.cpp.obj"
	cd C:/new_danya_cpp/build/saves && C:/msys64/ucrt64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT saves/CMakeFiles/saves.dir/saves.cpp.obj -MF CMakeFiles/saves.dir/saves.cpp.obj.d -o CMakeFiles/saves.dir/saves.cpp.obj -c C:/new_danya_cpp/saves/saves.cpp

saves/CMakeFiles/saves.dir/saves.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/saves.dir/saves.cpp.i"
	cd C:/new_danya_cpp/build/saves && C:/msys64/ucrt64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/new_danya_cpp/saves/saves.cpp > CMakeFiles/saves.dir/saves.cpp.i

saves/CMakeFiles/saves.dir/saves.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/saves.dir/saves.cpp.s"
	cd C:/new_danya_cpp/build/saves && C:/msys64/ucrt64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/new_danya_cpp/saves/saves.cpp -o CMakeFiles/saves.dir/saves.cpp.s

# Object files for target saves
saves_OBJECTS = \
"CMakeFiles/saves.dir/saves.cpp.obj"

# External object files for target saves
saves_EXTERNAL_OBJECTS =

saves/libsaves.a: saves/CMakeFiles/saves.dir/saves.cpp.obj
saves/libsaves.a: saves/CMakeFiles/saves.dir/build.make
saves/libsaves.a: saves/CMakeFiles/saves.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:/new_danya_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libsaves.a"
	cd C:/new_danya_cpp/build/saves && $(CMAKE_COMMAND) -P CMakeFiles/saves.dir/cmake_clean_target.cmake
	cd C:/new_danya_cpp/build/saves && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/saves.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
saves/CMakeFiles/saves.dir/build: saves/libsaves.a
.PHONY : saves/CMakeFiles/saves.dir/build

saves/CMakeFiles/saves.dir/clean:
	cd C:/new_danya_cpp/build/saves && $(CMAKE_COMMAND) -P CMakeFiles/saves.dir/cmake_clean.cmake
.PHONY : saves/CMakeFiles/saves.dir/clean

saves/CMakeFiles/saves.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/new_danya_cpp C:/new_danya_cpp/saves C:/new_danya_cpp/build C:/new_danya_cpp/build/saves C:/new_danya_cpp/build/saves/CMakeFiles/saves.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : saves/CMakeFiles/saves.dir/depend

