# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/bruno/Learning/ModernCppCV/BoW

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bruno/Learning/ModernCppCV/BoW/build

# Include any dependencies generated for this target.
include CMakeFiles/bow_dictionary.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bow_dictionary.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bow_dictionary.dir/flags.make

CMakeFiles/bow_dictionary.dir/src/bow_dictionary.cpp.o: CMakeFiles/bow_dictionary.dir/flags.make
CMakeFiles/bow_dictionary.dir/src/bow_dictionary.cpp.o: ../src/bow_dictionary.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bruno/Learning/ModernCppCV/BoW/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bow_dictionary.dir/src/bow_dictionary.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bow_dictionary.dir/src/bow_dictionary.cpp.o -c /home/bruno/Learning/ModernCppCV/BoW/src/bow_dictionary.cpp

CMakeFiles/bow_dictionary.dir/src/bow_dictionary.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bow_dictionary.dir/src/bow_dictionary.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bruno/Learning/ModernCppCV/BoW/src/bow_dictionary.cpp > CMakeFiles/bow_dictionary.dir/src/bow_dictionary.cpp.i

CMakeFiles/bow_dictionary.dir/src/bow_dictionary.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bow_dictionary.dir/src/bow_dictionary.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bruno/Learning/ModernCppCV/BoW/src/bow_dictionary.cpp -o CMakeFiles/bow_dictionary.dir/src/bow_dictionary.cpp.s

# Object files for target bow_dictionary
bow_dictionary_OBJECTS = \
"CMakeFiles/bow_dictionary.dir/src/bow_dictionary.cpp.o"

# External object files for target bow_dictionary
bow_dictionary_EXTERNAL_OBJECTS =

libbow_dictionary.a: CMakeFiles/bow_dictionary.dir/src/bow_dictionary.cpp.o
libbow_dictionary.a: CMakeFiles/bow_dictionary.dir/build.make
libbow_dictionary.a: CMakeFiles/bow_dictionary.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bruno/Learning/ModernCppCV/BoW/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libbow_dictionary.a"
	$(CMAKE_COMMAND) -P CMakeFiles/bow_dictionary.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bow_dictionary.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bow_dictionary.dir/build: libbow_dictionary.a

.PHONY : CMakeFiles/bow_dictionary.dir/build

CMakeFiles/bow_dictionary.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bow_dictionary.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bow_dictionary.dir/clean

CMakeFiles/bow_dictionary.dir/depend:
	cd /home/bruno/Learning/ModernCppCV/BoW/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bruno/Learning/ModernCppCV/BoW /home/bruno/Learning/ModernCppCV/BoW /home/bruno/Learning/ModernCppCV/BoW/build /home/bruno/Learning/ModernCppCV/BoW/build /home/bruno/Learning/ModernCppCV/BoW/build/CMakeFiles/bow_dictionary.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bow_dictionary.dir/depend

