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
CMAKE_SOURCE_DIR = /home/davidsim/Documents/Programming/IntegratedCompiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/davidsim/Documents/Programming/IntegratedCompiler/build

# Include any dependencies generated for this target.
include lexer/CMakeFiles/test_dfa.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lexer/CMakeFiles/test_dfa.dir/compiler_depend.make

# Include the progress variables for this target.
include lexer/CMakeFiles/test_dfa.dir/progress.make

# Include the compile flags for this target's objects.
include lexer/CMakeFiles/test_dfa.dir/flags.make

lexer/CMakeFiles/test_dfa.dir/test/test_dfa.cpp.o: lexer/CMakeFiles/test_dfa.dir/flags.make
lexer/CMakeFiles/test_dfa.dir/test/test_dfa.cpp.o: ../lexer/test/test_dfa.cpp
lexer/CMakeFiles/test_dfa.dir/test/test_dfa.cpp.o: lexer/CMakeFiles/test_dfa.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davidsim/Documents/Programming/IntegratedCompiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lexer/CMakeFiles/test_dfa.dir/test/test_dfa.cpp.o"
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/build/lexer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lexer/CMakeFiles/test_dfa.dir/test/test_dfa.cpp.o -MF CMakeFiles/test_dfa.dir/test/test_dfa.cpp.o.d -o CMakeFiles/test_dfa.dir/test/test_dfa.cpp.o -c /home/davidsim/Documents/Programming/IntegratedCompiler/lexer/test/test_dfa.cpp

lexer/CMakeFiles/test_dfa.dir/test/test_dfa.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_dfa.dir/test/test_dfa.cpp.i"
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/build/lexer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/davidsim/Documents/Programming/IntegratedCompiler/lexer/test/test_dfa.cpp > CMakeFiles/test_dfa.dir/test/test_dfa.cpp.i

lexer/CMakeFiles/test_dfa.dir/test/test_dfa.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_dfa.dir/test/test_dfa.cpp.s"
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/build/lexer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/davidsim/Documents/Programming/IntegratedCompiler/lexer/test/test_dfa.cpp -o CMakeFiles/test_dfa.dir/test/test_dfa.cpp.s

# Object files for target test_dfa
test_dfa_OBJECTS = \
"CMakeFiles/test_dfa.dir/test/test_dfa.cpp.o"

# External object files for target test_dfa
test_dfa_EXTERNAL_OBJECTS =

bin/test_dfa: lexer/CMakeFiles/test_dfa.dir/test/test_dfa.cpp.o
bin/test_dfa: lexer/CMakeFiles/test_dfa.dir/build.make
bin/test_dfa: lib/liblexer_lib.a
bin/test_dfa: lib/libgtest.a
bin/test_dfa: lib/libgtest_main.a
bin/test_dfa: lib/libgtest.a
bin/test_dfa: lexer/CMakeFiles/test_dfa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/davidsim/Documents/Programming/IntegratedCompiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/test_dfa"
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/build/lexer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_dfa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lexer/CMakeFiles/test_dfa.dir/build: bin/test_dfa
.PHONY : lexer/CMakeFiles/test_dfa.dir/build

lexer/CMakeFiles/test_dfa.dir/clean:
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/build/lexer && $(CMAKE_COMMAND) -P CMakeFiles/test_dfa.dir/cmake_clean.cmake
.PHONY : lexer/CMakeFiles/test_dfa.dir/clean

lexer/CMakeFiles/test_dfa.dir/depend:
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/davidsim/Documents/Programming/IntegratedCompiler /home/davidsim/Documents/Programming/IntegratedCompiler/lexer /home/davidsim/Documents/Programming/IntegratedCompiler/build /home/davidsim/Documents/Programming/IntegratedCompiler/build/lexer /home/davidsim/Documents/Programming/IntegratedCompiler/build/lexer/CMakeFiles/test_dfa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lexer/CMakeFiles/test_dfa.dir/depend

