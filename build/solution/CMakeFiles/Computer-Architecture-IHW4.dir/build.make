# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /snap/cmake/1359/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1359/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alex/Computer-Architecture-IHW4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/Computer-Architecture-IHW4/build

# Include any dependencies generated for this target.
include solution/CMakeFiles/Computer-Architecture-IHW4.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include solution/CMakeFiles/Computer-Architecture-IHW4.dir/compiler_depend.make

# Include the progress variables for this target.
include solution/CMakeFiles/Computer-Architecture-IHW4.dir/progress.make

# Include the compile flags for this target's objects.
include solution/CMakeFiles/Computer-Architecture-IHW4.dir/flags.make

solution/CMakeFiles/Computer-Architecture-IHW4.dir/main.cpp.o: solution/CMakeFiles/Computer-Architecture-IHW4.dir/flags.make
solution/CMakeFiles/Computer-Architecture-IHW4.dir/main.cpp.o: /home/alex/Computer-Architecture-IHW4/solution/main.cpp
solution/CMakeFiles/Computer-Architecture-IHW4.dir/main.cpp.o: solution/CMakeFiles/Computer-Architecture-IHW4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/alex/Computer-Architecture-IHW4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object solution/CMakeFiles/Computer-Architecture-IHW4.dir/main.cpp.o"
	cd /home/alex/Computer-Architecture-IHW4/build/solution && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT solution/CMakeFiles/Computer-Architecture-IHW4.dir/main.cpp.o -MF CMakeFiles/Computer-Architecture-IHW4.dir/main.cpp.o.d -o CMakeFiles/Computer-Architecture-IHW4.dir/main.cpp.o -c /home/alex/Computer-Architecture-IHW4/solution/main.cpp

solution/CMakeFiles/Computer-Architecture-IHW4.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Computer-Architecture-IHW4.dir/main.cpp.i"
	cd /home/alex/Computer-Architecture-IHW4/build/solution && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Computer-Architecture-IHW4/solution/main.cpp > CMakeFiles/Computer-Architecture-IHW4.dir/main.cpp.i

solution/CMakeFiles/Computer-Architecture-IHW4.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Computer-Architecture-IHW4.dir/main.cpp.s"
	cd /home/alex/Computer-Architecture-IHW4/build/solution && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Computer-Architecture-IHW4/solution/main.cpp -o CMakeFiles/Computer-Architecture-IHW4.dir/main.cpp.s

# Object files for target Computer-Architecture-IHW4
Computer__Architecture__IHW4_OBJECTS = \
"CMakeFiles/Computer-Architecture-IHW4.dir/main.cpp.o"

# External object files for target Computer-Architecture-IHW4
Computer__Architecture__IHW4_EXTERNAL_OBJECTS =

solution/Computer-Architecture-IHW4: solution/CMakeFiles/Computer-Architecture-IHW4.dir/main.cpp.o
solution/Computer-Architecture-IHW4: solution/CMakeFiles/Computer-Architecture-IHW4.dir/build.make
solution/Computer-Architecture-IHW4: solution/CMakeFiles/Computer-Architecture-IHW4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/alex/Computer-Architecture-IHW4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Computer-Architecture-IHW4"
	cd /home/alex/Computer-Architecture-IHW4/build/solution && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Computer-Architecture-IHW4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
solution/CMakeFiles/Computer-Architecture-IHW4.dir/build: solution/Computer-Architecture-IHW4
.PHONY : solution/CMakeFiles/Computer-Architecture-IHW4.dir/build

solution/CMakeFiles/Computer-Architecture-IHW4.dir/clean:
	cd /home/alex/Computer-Architecture-IHW4/build/solution && $(CMAKE_COMMAND) -P CMakeFiles/Computer-Architecture-IHW4.dir/cmake_clean.cmake
.PHONY : solution/CMakeFiles/Computer-Architecture-IHW4.dir/clean

solution/CMakeFiles/Computer-Architecture-IHW4.dir/depend:
	cd /home/alex/Computer-Architecture-IHW4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/Computer-Architecture-IHW4 /home/alex/Computer-Architecture-IHW4/solution /home/alex/Computer-Architecture-IHW4/build /home/alex/Computer-Architecture-IHW4/build/solution /home/alex/Computer-Architecture-IHW4/build/solution/CMakeFiles/Computer-Architecture-IHW4.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : solution/CMakeFiles/Computer-Architecture-IHW4.dir/depend
