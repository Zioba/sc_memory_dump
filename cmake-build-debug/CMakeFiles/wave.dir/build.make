# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/alexander/work/clion-2019.3.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/alexander/work/clion-2019.3.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alexander/work/sc_memory_dump

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexander/work/sc_memory_dump/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/wave.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wave.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wave.dir/flags.make

CMakeFiles/wave.dir/wavefindpath.cpp.o: CMakeFiles/wave.dir/flags.make
CMakeFiles/wave.dir/wavefindpath.cpp.o: ../wavefindpath.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexander/work/sc_memory_dump/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wave.dir/wavefindpath.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wave.dir/wavefindpath.cpp.o -c /home/alexander/work/sc_memory_dump/wavefindpath.cpp

CMakeFiles/wave.dir/wavefindpath.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wave.dir/wavefindpath.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexander/work/sc_memory_dump/wavefindpath.cpp > CMakeFiles/wave.dir/wavefindpath.cpp.i

CMakeFiles/wave.dir/wavefindpath.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wave.dir/wavefindpath.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexander/work/sc_memory_dump/wavefindpath.cpp -o CMakeFiles/wave.dir/wavefindpath.cpp.s

CMakeFiles/wave.dir/utils.cpp.o: CMakeFiles/wave.dir/flags.make
CMakeFiles/wave.dir/utils.cpp.o: ../utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexander/work/sc_memory_dump/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/wave.dir/utils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wave.dir/utils.cpp.o -c /home/alexander/work/sc_memory_dump/utils.cpp

CMakeFiles/wave.dir/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wave.dir/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexander/work/sc_memory_dump/utils.cpp > CMakeFiles/wave.dir/utils.cpp.i

CMakeFiles/wave.dir/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wave.dir/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexander/work/sc_memory_dump/utils.cpp -o CMakeFiles/wave.dir/utils.cpp.s

CMakeFiles/wave.dir/model/Node.cpp.o: CMakeFiles/wave.dir/flags.make
CMakeFiles/wave.dir/model/Node.cpp.o: ../model/Node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexander/work/sc_memory_dump/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/wave.dir/model/Node.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wave.dir/model/Node.cpp.o -c /home/alexander/work/sc_memory_dump/model/Node.cpp

CMakeFiles/wave.dir/model/Node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wave.dir/model/Node.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexander/work/sc_memory_dump/model/Node.cpp > CMakeFiles/wave.dir/model/Node.cpp.i

CMakeFiles/wave.dir/model/Node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wave.dir/model/Node.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexander/work/sc_memory_dump/model/Node.cpp -o CMakeFiles/wave.dir/model/Node.cpp.s

CMakeFiles/wave.dir/model/Edge.cpp.o: CMakeFiles/wave.dir/flags.make
CMakeFiles/wave.dir/model/Edge.cpp.o: ../model/Edge.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexander/work/sc_memory_dump/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/wave.dir/model/Edge.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wave.dir/model/Edge.cpp.o -c /home/alexander/work/sc_memory_dump/model/Edge.cpp

CMakeFiles/wave.dir/model/Edge.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wave.dir/model/Edge.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexander/work/sc_memory_dump/model/Edge.cpp > CMakeFiles/wave.dir/model/Edge.cpp.i

CMakeFiles/wave.dir/model/Edge.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wave.dir/model/Edge.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexander/work/sc_memory_dump/model/Edge.cpp -o CMakeFiles/wave.dir/model/Edge.cpp.s

# Object files for target wave
wave_OBJECTS = \
"CMakeFiles/wave.dir/wavefindpath.cpp.o" \
"CMakeFiles/wave.dir/utils.cpp.o" \
"CMakeFiles/wave.dir/model/Node.cpp.o" \
"CMakeFiles/wave.dir/model/Edge.cpp.o"

# External object files for target wave
wave_EXTERNAL_OBJECTS =

/home/alexander/work/ostis/sc-machine/bin/wave: CMakeFiles/wave.dir/wavefindpath.cpp.o
/home/alexander/work/ostis/sc-machine/bin/wave: CMakeFiles/wave.dir/utils.cpp.o
/home/alexander/work/ostis/sc-machine/bin/wave: CMakeFiles/wave.dir/model/Node.cpp.o
/home/alexander/work/ostis/sc-machine/bin/wave: CMakeFiles/wave.dir/model/Edge.cpp.o
/home/alexander/work/ostis/sc-machine/bin/wave: CMakeFiles/wave.dir/build.make
/home/alexander/work/ostis/sc-machine/bin/wave: CMakeFiles/wave.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alexander/work/sc_memory_dump/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable /home/alexander/work/ostis/sc-machine/bin/wave"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wave.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wave.dir/build: /home/alexander/work/ostis/sc-machine/bin/wave

.PHONY : CMakeFiles/wave.dir/build

CMakeFiles/wave.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wave.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wave.dir/clean

CMakeFiles/wave.dir/depend:
	cd /home/alexander/work/sc_memory_dump/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexander/work/sc_memory_dump /home/alexander/work/sc_memory_dump /home/alexander/work/sc_memory_dump/cmake-build-debug /home/alexander/work/sc_memory_dump/cmake-build-debug /home/alexander/work/sc_memory_dump/cmake-build-debug/CMakeFiles/wave.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/wave.dir/depend

