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
CMAKE_BINARY_DIR = /home/davidsim/Documents/Programming/IntegratedCompiler

# Include any dependencies generated for this target.
include lexer/CMakeFiles/lexer_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lexer/CMakeFiles/lexer_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include lexer/CMakeFiles/lexer_lib.dir/progress.make

# Include the compile flags for this target's objects.
include lexer/CMakeFiles/lexer_lib.dir/flags.make

lexer/CMakeFiles/lexer_lib.dir/src/dfa.cpp.o: lexer/CMakeFiles/lexer_lib.dir/flags.make
lexer/CMakeFiles/lexer_lib.dir/src/dfa.cpp.o: lexer/src/dfa.cpp
lexer/CMakeFiles/lexer_lib.dir/src/dfa.cpp.o: lexer/CMakeFiles/lexer_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davidsim/Documents/Programming/IntegratedCompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lexer/CMakeFiles/lexer_lib.dir/src/dfa.cpp.o"
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/lexer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lexer/CMakeFiles/lexer_lib.dir/src/dfa.cpp.o -MF CMakeFiles/lexer_lib.dir/src/dfa.cpp.o.d -o CMakeFiles/lexer_lib.dir/src/dfa.cpp.o -c /home/davidsim/Documents/Programming/IntegratedCompiler/lexer/src/dfa.cpp

lexer/CMakeFiles/lexer_lib.dir/src/dfa.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lexer_lib.dir/src/dfa.cpp.i"
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/lexer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/davidsim/Documents/Programming/IntegratedCompiler/lexer/src/dfa.cpp > CMakeFiles/lexer_lib.dir/src/dfa.cpp.i

lexer/CMakeFiles/lexer_lib.dir/src/dfa.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lexer_lib.dir/src/dfa.cpp.s"
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/lexer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/davidsim/Documents/Programming/IntegratedCompiler/lexer/src/dfa.cpp -o CMakeFiles/lexer_lib.dir/src/dfa.cpp.s

lexer/CMakeFiles/lexer_lib.dir/src/nfa.cpp.o: lexer/CMakeFiles/lexer_lib.dir/flags.make
lexer/CMakeFiles/lexer_lib.dir/src/nfa.cpp.o: lexer/src/nfa.cpp
lexer/CMakeFiles/lexer_lib.dir/src/nfa.cpp.o: lexer/CMakeFiles/lexer_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davidsim/Documents/Programming/IntegratedCompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lexer/CMakeFiles/lexer_lib.dir/src/nfa.cpp.o"
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/lexer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lexer/CMakeFiles/lexer_lib.dir/src/nfa.cpp.o -MF CMakeFiles/lexer_lib.dir/src/nfa.cpp.o.d -o CMakeFiles/lexer_lib.dir/src/nfa.cpp.o -c /home/davidsim/Documents/Programming/IntegratedCompiler/lexer/src/nfa.cpp

lexer/CMakeFiles/lexer_lib.dir/src/nfa.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lexer_lib.dir/src/nfa.cpp.i"
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/lexer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/davidsim/Documents/Programming/IntegratedCompiler/lexer/src/nfa.cpp > CMakeFiles/lexer_lib.dir/src/nfa.cpp.i

lexer/CMakeFiles/lexer_lib.dir/src/nfa.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lexer_lib.dir/src/nfa.cpp.s"
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/lexer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/davidsim/Documents/Programming/IntegratedCompiler/lexer/src/nfa.cpp -o CMakeFiles/lexer_lib.dir/src/nfa.cpp.s

lexer/CMakeFiles/lexer_lib.dir/src/re.cpp.o: lexer/CMakeFiles/lexer_lib.dir/flags.make
lexer/CMakeFiles/lexer_lib.dir/src/re.cpp.o: lexer/src/re.cpp
lexer/CMakeFiles/lexer_lib.dir/src/re.cpp.o: lexer/CMakeFiles/lexer_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davidsim/Documents/Programming/IntegratedCompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lexer/CMakeFiles/lexer_lib.dir/src/re.cpp.o"
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/lexer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lexer/CMakeFiles/lexer_lib.dir/src/re.cpp.o -MF CMakeFiles/lexer_lib.dir/src/re.cpp.o.d -o CMakeFiles/lexer_lib.dir/src/re.cpp.o -c /home/davidsim/Documents/Programming/IntegratedCompiler/lexer/src/re.cpp

lexer/CMakeFiles/lexer_lib.dir/src/re.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lexer_lib.dir/src/re.cpp.i"
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/lexer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/davidsim/Documents/Programming/IntegratedCompiler/lexer/src/re.cpp > CMakeFiles/lexer_lib.dir/src/re.cpp.i

lexer/CMakeFiles/lexer_lib.dir/src/re.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lexer_lib.dir/src/re.cpp.s"
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/lexer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/davidsim/Documents/Programming/IntegratedCompiler/lexer/src/re.cpp -o CMakeFiles/lexer_lib.dir/src/re.cpp.s

# Object files for target lexer_lib
lexer_lib_OBJECTS = \
"CMakeFiles/lexer_lib.dir/src/dfa.cpp.o" \
"CMakeFiles/lexer_lib.dir/src/nfa.cpp.o" \
"CMakeFiles/lexer_lib.dir/src/re.cpp.o"

# External object files for target lexer_lib
lexer_lib_EXTERNAL_OBJECTS =

lib/liblexer_lib.a: lexer/CMakeFiles/lexer_lib.dir/src/dfa.cpp.o
lib/liblexer_lib.a: lexer/CMakeFiles/lexer_lib.dir/src/nfa.cpp.o
lib/liblexer_lib.a: lexer/CMakeFiles/lexer_lib.dir/src/re.cpp.o
lib/liblexer_lib.a: lexer/CMakeFiles/lexer_lib.dir/build.make
lib/liblexer_lib.a: lexer/CMakeFiles/lexer_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/davidsim/Documents/Programming/IntegratedCompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library ../lib/liblexer_lib.a"
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/lexer && $(CMAKE_COMMAND) -P CMakeFiles/lexer_lib.dir/cmake_clean_target.cmake
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/lexer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lexer_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lexer/CMakeFiles/lexer_lib.dir/build: lib/liblexer_lib.a
.PHONY : lexer/CMakeFiles/lexer_lib.dir/build

lexer/CMakeFiles/lexer_lib.dir/clean:
	cd /home/davidsim/Documents/Programming/IntegratedCompiler/lexer && $(CMAKE_COMMAND) -P CMakeFiles/lexer_lib.dir/cmake_clean.cmake
.PHONY : lexer/CMakeFiles/lexer_lib.dir/clean

lexer/CMakeFiles/lexer_lib.dir/depend:
	cd /home/davidsim/Documents/Programming/IntegratedCompiler && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/davidsim/Documents/Programming/IntegratedCompiler /home/davidsim/Documents/Programming/IntegratedCompiler/lexer /home/davidsim/Documents/Programming/IntegratedCompiler /home/davidsim/Documents/Programming/IntegratedCompiler/lexer /home/davidsim/Documents/Programming/IntegratedCompiler/lexer/CMakeFiles/lexer_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lexer/CMakeFiles/lexer_lib.dir/depend

