# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/connorbrookes/Documents/Uni/Graphics Project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/connorbrookes/Documents/Uni/Graphics Project/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Graphics_Project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Graphics_Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Graphics_Project.dir/flags.make

CMakeFiles/Graphics_Project.dir/main.cpp.o: CMakeFiles/Graphics_Project.dir/flags.make
CMakeFiles/Graphics_Project.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/connorbrookes/Documents/Uni/Graphics Project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Graphics_Project.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Graphics_Project.dir/main.cpp.o -c "/Users/connorbrookes/Documents/Uni/Graphics Project/main.cpp"

CMakeFiles/Graphics_Project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Graphics_Project.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/connorbrookes/Documents/Uni/Graphics Project/main.cpp" > CMakeFiles/Graphics_Project.dir/main.cpp.i

CMakeFiles/Graphics_Project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Graphics_Project.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/connorbrookes/Documents/Uni/Graphics Project/main.cpp" -o CMakeFiles/Graphics_Project.dir/main.cpp.s

CMakeFiles/Graphics_Project.dir/oneParticle.cpp.o: CMakeFiles/Graphics_Project.dir/flags.make
CMakeFiles/Graphics_Project.dir/oneParticle.cpp.o: ../oneParticle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/connorbrookes/Documents/Uni/Graphics Project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Graphics_Project.dir/oneParticle.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Graphics_Project.dir/oneParticle.cpp.o -c "/Users/connorbrookes/Documents/Uni/Graphics Project/oneParticle.cpp"

CMakeFiles/Graphics_Project.dir/oneParticle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Graphics_Project.dir/oneParticle.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/connorbrookes/Documents/Uni/Graphics Project/oneParticle.cpp" > CMakeFiles/Graphics_Project.dir/oneParticle.cpp.i

CMakeFiles/Graphics_Project.dir/oneParticle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Graphics_Project.dir/oneParticle.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/connorbrookes/Documents/Uni/Graphics Project/oneParticle.cpp" -o CMakeFiles/Graphics_Project.dir/oneParticle.cpp.s

CMakeFiles/Graphics_Project.dir/example.cpp.o: CMakeFiles/Graphics_Project.dir/flags.make
CMakeFiles/Graphics_Project.dir/example.cpp.o: ../example.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/connorbrookes/Documents/Uni/Graphics Project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Graphics_Project.dir/example.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Graphics_Project.dir/example.cpp.o -c "/Users/connorbrookes/Documents/Uni/Graphics Project/example.cpp"

CMakeFiles/Graphics_Project.dir/example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Graphics_Project.dir/example.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/connorbrookes/Documents/Uni/Graphics Project/example.cpp" > CMakeFiles/Graphics_Project.dir/example.cpp.i

CMakeFiles/Graphics_Project.dir/example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Graphics_Project.dir/example.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/connorbrookes/Documents/Uni/Graphics Project/example.cpp" -o CMakeFiles/Graphics_Project.dir/example.cpp.s

# Object files for target Graphics_Project
Graphics_Project_OBJECTS = \
"CMakeFiles/Graphics_Project.dir/main.cpp.o" \
"CMakeFiles/Graphics_Project.dir/oneParticle.cpp.o" \
"CMakeFiles/Graphics_Project.dir/example.cpp.o"

# External object files for target Graphics_Project
Graphics_Project_EXTERNAL_OBJECTS =

Graphics_Project: CMakeFiles/Graphics_Project.dir/main.cpp.o
Graphics_Project: CMakeFiles/Graphics_Project.dir/oneParticle.cpp.o
Graphics_Project: CMakeFiles/Graphics_Project.dir/example.cpp.o
Graphics_Project: CMakeFiles/Graphics_Project.dir/build.make
Graphics_Project: CMakeFiles/Graphics_Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/connorbrookes/Documents/Uni/Graphics Project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Graphics_Project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Graphics_Project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Graphics_Project.dir/build: Graphics_Project

.PHONY : CMakeFiles/Graphics_Project.dir/build

CMakeFiles/Graphics_Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Graphics_Project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Graphics_Project.dir/clean

CMakeFiles/Graphics_Project.dir/depend:
	cd "/Users/connorbrookes/Documents/Uni/Graphics Project/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/connorbrookes/Documents/Uni/Graphics Project" "/Users/connorbrookes/Documents/Uni/Graphics Project" "/Users/connorbrookes/Documents/Uni/Graphics Project/cmake-build-debug" "/Users/connorbrookes/Documents/Uni/Graphics Project/cmake-build-debug" "/Users/connorbrookes/Documents/Uni/Graphics Project/cmake-build-debug/CMakeFiles/Graphics_Project.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Graphics_Project.dir/depend

