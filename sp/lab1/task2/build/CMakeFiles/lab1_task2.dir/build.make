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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/build

# Include any dependencies generated for this target.
include CMakeFiles/lab1_task2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lab1_task2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lab1_task2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab1_task2.dir/flags.make

CMakeFiles/lab1_task2.dir/main.c.o: CMakeFiles/lab1_task2.dir/flags.make
CMakeFiles/lab1_task2.dir/main.c.o: /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/main.c
CMakeFiles/lab1_task2.dir/main.c.o: CMakeFiles/lab1_task2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lab1_task2.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lab1_task2.dir/main.c.o -MF CMakeFiles/lab1_task2.dir/main.c.o.d -o CMakeFiles/lab1_task2.dir/main.c.o -c /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/main.c

CMakeFiles/lab1_task2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lab1_task2.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/main.c > CMakeFiles/lab1_task2.dir/main.c.i

CMakeFiles/lab1_task2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lab1_task2.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/main.c -o CMakeFiles/lab1_task2.dir/main.c.s

CMakeFiles/lab1_task2.dir/funcs.c.o: CMakeFiles/lab1_task2.dir/flags.make
CMakeFiles/lab1_task2.dir/funcs.c.o: /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/funcs.c
CMakeFiles/lab1_task2.dir/funcs.c.o: CMakeFiles/lab1_task2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/lab1_task2.dir/funcs.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lab1_task2.dir/funcs.c.o -MF CMakeFiles/lab1_task2.dir/funcs.c.o.d -o CMakeFiles/lab1_task2.dir/funcs.c.o -c /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/funcs.c

CMakeFiles/lab1_task2.dir/funcs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lab1_task2.dir/funcs.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/funcs.c > CMakeFiles/lab1_task2.dir/funcs.c.i

CMakeFiles/lab1_task2.dir/funcs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lab1_task2.dir/funcs.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/funcs.c -o CMakeFiles/lab1_task2.dir/funcs.c.s

# Object files for target lab1_task2
lab1_task2_OBJECTS = \
"CMakeFiles/lab1_task2.dir/main.c.o" \
"CMakeFiles/lab1_task2.dir/funcs.c.o"

# External object files for target lab1_task2
lab1_task2_EXTERNAL_OBJECTS =

lab1_task2: CMakeFiles/lab1_task2.dir/main.c.o
lab1_task2: CMakeFiles/lab1_task2.dir/funcs.c.o
lab1_task2: CMakeFiles/lab1_task2.dir/build.make
lab1_task2: CMakeFiles/lab1_task2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable lab1_task2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab1_task2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab1_task2.dir/build: lab1_task2
.PHONY : CMakeFiles/lab1_task2.dir/build

CMakeFiles/lab1_task2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab1_task2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab1_task2.dir/clean

CMakeFiles/lab1_task2.dir/depend:
	cd /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2 /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2 /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/build /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/build /mnt/c/Users/mrbor/CLionProjects/fund_algs_sp/sp/lab1/task2/build/CMakeFiles/lab1_task2.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/lab1_task2.dir/depend

