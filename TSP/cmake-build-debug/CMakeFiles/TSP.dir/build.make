# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\clion\CLion 2020.1.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\clion\CLion 2020.1.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\66919\TSP-Course-Design\TSP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\66919\TSP-Course-Design\TSP\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TSP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TSP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TSP.dir/flags.make

CMakeFiles/TSP.dir/main.cpp.obj: CMakeFiles/TSP.dir/flags.make
CMakeFiles/TSP.dir/main.cpp.obj: CMakeFiles/TSP.dir/includes_CXX.rsp
CMakeFiles/TSP.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\66919\TSP-Course-Design\TSP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TSP.dir/main.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TSP.dir\main.cpp.obj -c C:\Users\66919\TSP-Course-Design\TSP\main.cpp

CMakeFiles/TSP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TSP.dir/main.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\66919\TSP-Course-Design\TSP\main.cpp > CMakeFiles\TSP.dir\main.cpp.i

CMakeFiles/TSP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TSP.dir/main.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\66919\TSP-Course-Design\TSP\main.cpp -o CMakeFiles\TSP.dir\main.cpp.s

# Object files for target TSP
TSP_OBJECTS = \
"CMakeFiles/TSP.dir/main.cpp.obj"

# External object files for target TSP
TSP_EXTERNAL_OBJECTS =

TSP.exe: CMakeFiles/TSP.dir/main.cpp.obj
TSP.exe: CMakeFiles/TSP.dir/build.make
TSP.exe: testAlgo/libtestAlgo.a
TSP.exe: readFile/libreadFile.a
TSP.exe: Ant/libant.a
TSP.exe: Tabu/libtabu.a
TSP.exe: insertion/libinsertion.a
TSP.exe: greedyKNN/libgreedyKNN.a
TSP.exe: CMakeFiles/TSP.dir/linklibs.rsp
TSP.exe: CMakeFiles/TSP.dir/objects1.rsp
TSP.exe: CMakeFiles/TSP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\66919\TSP-Course-Design\TSP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TSP.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\TSP.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TSP.dir/build: TSP.exe

.PHONY : CMakeFiles/TSP.dir/build

CMakeFiles/TSP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\TSP.dir\cmake_clean.cmake
.PHONY : CMakeFiles/TSP.dir/clean

CMakeFiles/TSP.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\66919\TSP-Course-Design\TSP C:\Users\66919\TSP-Course-Design\TSP C:\Users\66919\TSP-Course-Design\TSP\cmake-build-debug C:\Users\66919\TSP-Course-Design\TSP\cmake-build-debug C:\Users\66919\TSP-Course-Design\TSP\cmake-build-debug\CMakeFiles\TSP.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TSP.dir/depend

