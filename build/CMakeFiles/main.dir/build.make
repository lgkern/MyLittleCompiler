# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/grad/hmroesler/MyLittleCompiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/grad/hmroesler/MyLittleCompiler/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/scanner.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/scanner.c.o: scanner.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/grad/hmroesler/MyLittleCompiler/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/scanner.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/scanner.c.o   -c /home/grad/hmroesler/MyLittleCompiler/build/scanner.c

CMakeFiles/main.dir/scanner.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/scanner.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/grad/hmroesler/MyLittleCompiler/build/scanner.c > CMakeFiles/main.dir/scanner.c.i

CMakeFiles/main.dir/scanner.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/scanner.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/grad/hmroesler/MyLittleCompiler/build/scanner.c -o CMakeFiles/main.dir/scanner.c.s

CMakeFiles/main.dir/scanner.c.o.requires:
.PHONY : CMakeFiles/main.dir/scanner.c.o.requires

CMakeFiles/main.dir/scanner.c.o.provides: CMakeFiles/main.dir/scanner.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/scanner.c.o.provides.build
.PHONY : CMakeFiles/main.dir/scanner.c.o.provides

CMakeFiles/main.dir/scanner.c.o.provides.build: CMakeFiles/main.dir/scanner.c.o

CMakeFiles/main.dir/parser.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/parser.c.o: parser.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/grad/hmroesler/MyLittleCompiler/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/parser.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/parser.c.o   -c /home/grad/hmroesler/MyLittleCompiler/build/parser.c

CMakeFiles/main.dir/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/parser.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/grad/hmroesler/MyLittleCompiler/build/parser.c > CMakeFiles/main.dir/parser.c.i

CMakeFiles/main.dir/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/parser.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/grad/hmroesler/MyLittleCompiler/build/parser.c -o CMakeFiles/main.dir/parser.c.s

CMakeFiles/main.dir/parser.c.o.requires:
.PHONY : CMakeFiles/main.dir/parser.c.o.requires

CMakeFiles/main.dir/parser.c.o.provides: CMakeFiles/main.dir/parser.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/parser.c.o.provides.build
.PHONY : CMakeFiles/main.dir/parser.c.o.provides

CMakeFiles/main.dir/parser.c.o.provides.build: CMakeFiles/main.dir/parser.c.o

CMakeFiles/main.dir/src/main.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/main.c.o: ../src/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/grad/hmroesler/MyLittleCompiler/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/src/main.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/src/main.c.o   -c /home/grad/hmroesler/MyLittleCompiler/src/main.c

CMakeFiles/main.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/main.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/grad/hmroesler/MyLittleCompiler/src/main.c > CMakeFiles/main.dir/src/main.c.i

CMakeFiles/main.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/main.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/grad/hmroesler/MyLittleCompiler/src/main.c -o CMakeFiles/main.dir/src/main.c.s

CMakeFiles/main.dir/src/main.c.o.requires:
.PHONY : CMakeFiles/main.dir/src/main.c.o.requires

CMakeFiles/main.dir/src/main.c.o.provides: CMakeFiles/main.dir/src/main.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/main.c.o.provides.build
.PHONY : CMakeFiles/main.dir/src/main.c.o.provides

CMakeFiles/main.dir/src/main.c.o.provides.build: CMakeFiles/main.dir/src/main.c.o

CMakeFiles/main.dir/src/misc.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/misc.c.o: ../src/misc.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/grad/hmroesler/MyLittleCompiler/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/src/misc.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/src/misc.c.o   -c /home/grad/hmroesler/MyLittleCompiler/src/misc.c

CMakeFiles/main.dir/src/misc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/misc.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/grad/hmroesler/MyLittleCompiler/src/misc.c > CMakeFiles/main.dir/src/misc.c.i

CMakeFiles/main.dir/src/misc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/misc.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/grad/hmroesler/MyLittleCompiler/src/misc.c -o CMakeFiles/main.dir/src/misc.c.s

CMakeFiles/main.dir/src/misc.c.o.requires:
.PHONY : CMakeFiles/main.dir/src/misc.c.o.requires

CMakeFiles/main.dir/src/misc.c.o.provides: CMakeFiles/main.dir/src/misc.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/misc.c.o.provides.build
.PHONY : CMakeFiles/main.dir/src/misc.c.o.provides

CMakeFiles/main.dir/src/misc.c.o.provides.build: CMakeFiles/main.dir/src/misc.c.o

CMakeFiles/main.dir/src/gv.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/gv.c.o: ../src/gv.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/grad/hmroesler/MyLittleCompiler/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/src/gv.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/src/gv.c.o   -c /home/grad/hmroesler/MyLittleCompiler/src/gv.c

CMakeFiles/main.dir/src/gv.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/gv.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/grad/hmroesler/MyLittleCompiler/src/gv.c > CMakeFiles/main.dir/src/gv.c.i

CMakeFiles/main.dir/src/gv.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/gv.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/grad/hmroesler/MyLittleCompiler/src/gv.c -o CMakeFiles/main.dir/src/gv.c.s

CMakeFiles/main.dir/src/gv.c.o.requires:
.PHONY : CMakeFiles/main.dir/src/gv.c.o.requires

CMakeFiles/main.dir/src/gv.c.o.provides: CMakeFiles/main.dir/src/gv.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/gv.c.o.provides.build
.PHONY : CMakeFiles/main.dir/src/gv.c.o.provides

CMakeFiles/main.dir/src/gv.c.o.provides.build: CMakeFiles/main.dir/src/gv.c.o

CMakeFiles/main.dir/src/comp_dict.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/comp_dict.c.o: ../src/comp_dict.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/grad/hmroesler/MyLittleCompiler/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/src/comp_dict.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/src/comp_dict.c.o   -c /home/grad/hmroesler/MyLittleCompiler/src/comp_dict.c

CMakeFiles/main.dir/src/comp_dict.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/comp_dict.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/grad/hmroesler/MyLittleCompiler/src/comp_dict.c > CMakeFiles/main.dir/src/comp_dict.c.i

CMakeFiles/main.dir/src/comp_dict.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/comp_dict.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/grad/hmroesler/MyLittleCompiler/src/comp_dict.c -o CMakeFiles/main.dir/src/comp_dict.c.s

CMakeFiles/main.dir/src/comp_dict.c.o.requires:
.PHONY : CMakeFiles/main.dir/src/comp_dict.c.o.requires

CMakeFiles/main.dir/src/comp_dict.c.o.provides: CMakeFiles/main.dir/src/comp_dict.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/comp_dict.c.o.provides.build
.PHONY : CMakeFiles/main.dir/src/comp_dict.c.o.provides

CMakeFiles/main.dir/src/comp_dict.c.o.provides.build: CMakeFiles/main.dir/src/comp_dict.c.o

CMakeFiles/main.dir/src/comp_list.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/comp_list.c.o: ../src/comp_list.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/grad/hmroesler/MyLittleCompiler/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/src/comp_list.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/src/comp_list.c.o   -c /home/grad/hmroesler/MyLittleCompiler/src/comp_list.c

CMakeFiles/main.dir/src/comp_list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/comp_list.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/grad/hmroesler/MyLittleCompiler/src/comp_list.c > CMakeFiles/main.dir/src/comp_list.c.i

CMakeFiles/main.dir/src/comp_list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/comp_list.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/grad/hmroesler/MyLittleCompiler/src/comp_list.c -o CMakeFiles/main.dir/src/comp_list.c.s

CMakeFiles/main.dir/src/comp_list.c.o.requires:
.PHONY : CMakeFiles/main.dir/src/comp_list.c.o.requires

CMakeFiles/main.dir/src/comp_list.c.o.provides: CMakeFiles/main.dir/src/comp_list.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/comp_list.c.o.provides.build
.PHONY : CMakeFiles/main.dir/src/comp_list.c.o.provides

CMakeFiles/main.dir/src/comp_list.c.o.provides.build: CMakeFiles/main.dir/src/comp_list.c.o

CMakeFiles/main.dir/src/comp_tree.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/comp_tree.c.o: ../src/comp_tree.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/grad/hmroesler/MyLittleCompiler/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/src/comp_tree.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/src/comp_tree.c.o   -c /home/grad/hmroesler/MyLittleCompiler/src/comp_tree.c

CMakeFiles/main.dir/src/comp_tree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/comp_tree.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/grad/hmroesler/MyLittleCompiler/src/comp_tree.c > CMakeFiles/main.dir/src/comp_tree.c.i

CMakeFiles/main.dir/src/comp_tree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/comp_tree.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/grad/hmroesler/MyLittleCompiler/src/comp_tree.c -o CMakeFiles/main.dir/src/comp_tree.c.s

CMakeFiles/main.dir/src/comp_tree.c.o.requires:
.PHONY : CMakeFiles/main.dir/src/comp_tree.c.o.requires

CMakeFiles/main.dir/src/comp_tree.c.o.provides: CMakeFiles/main.dir/src/comp_tree.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/comp_tree.c.o.provides.build
.PHONY : CMakeFiles/main.dir/src/comp_tree.c.o.provides

CMakeFiles/main.dir/src/comp_tree.c.o.provides.build: CMakeFiles/main.dir/src/comp_tree.c.o

CMakeFiles/main.dir/src/symbtable.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/symbtable.c.o: ../src/symbtable.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/grad/hmroesler/MyLittleCompiler/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/src/symbtable.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/src/symbtable.c.o   -c /home/grad/hmroesler/MyLittleCompiler/src/symbtable.c

CMakeFiles/main.dir/src/symbtable.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/symbtable.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/grad/hmroesler/MyLittleCompiler/src/symbtable.c > CMakeFiles/main.dir/src/symbtable.c.i

CMakeFiles/main.dir/src/symbtable.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/symbtable.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/grad/hmroesler/MyLittleCompiler/src/symbtable.c -o CMakeFiles/main.dir/src/symbtable.c.s

CMakeFiles/main.dir/src/symbtable.c.o.requires:
.PHONY : CMakeFiles/main.dir/src/symbtable.c.o.requires

CMakeFiles/main.dir/src/symbtable.c.o.provides: CMakeFiles/main.dir/src/symbtable.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/symbtable.c.o.provides.build
.PHONY : CMakeFiles/main.dir/src/symbtable.c.o.provides

CMakeFiles/main.dir/src/symbtable.c.o.provides.build: CMakeFiles/main.dir/src/symbtable.c.o

CMakeFiles/main.dir/src/symt.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/symt.c.o: ../src/symt.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/grad/hmroesler/MyLittleCompiler/build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/src/symt.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/src/symt.c.o   -c /home/grad/hmroesler/MyLittleCompiler/src/symt.c

CMakeFiles/main.dir/src/symt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/symt.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/grad/hmroesler/MyLittleCompiler/src/symt.c > CMakeFiles/main.dir/src/symt.c.i

CMakeFiles/main.dir/src/symt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/symt.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/grad/hmroesler/MyLittleCompiler/src/symt.c -o CMakeFiles/main.dir/src/symt.c.s

CMakeFiles/main.dir/src/symt.c.o.requires:
.PHONY : CMakeFiles/main.dir/src/symt.c.o.requires

CMakeFiles/main.dir/src/symt.c.o.provides: CMakeFiles/main.dir/src/symt.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/symt.c.o.provides.build
.PHONY : CMakeFiles/main.dir/src/symt.c.o.provides

CMakeFiles/main.dir/src/symt.c.o.provides.build: CMakeFiles/main.dir/src/symt.c.o

CMakeFiles/main.dir/src/crc16.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/crc16.c.o: ../src/crc16.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/grad/hmroesler/MyLittleCompiler/build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/main.dir/src/crc16.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/main.dir/src/crc16.c.o   -c /home/grad/hmroesler/MyLittleCompiler/src/crc16.c

CMakeFiles/main.dir/src/crc16.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/crc16.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/grad/hmroesler/MyLittleCompiler/src/crc16.c > CMakeFiles/main.dir/src/crc16.c.i

CMakeFiles/main.dir/src/crc16.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/crc16.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/grad/hmroesler/MyLittleCompiler/src/crc16.c -o CMakeFiles/main.dir/src/crc16.c.s

CMakeFiles/main.dir/src/crc16.c.o.requires:
.PHONY : CMakeFiles/main.dir/src/crc16.c.o.requires

CMakeFiles/main.dir/src/crc16.c.o.provides: CMakeFiles/main.dir/src/crc16.c.o.requires
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/crc16.c.o.provides.build
.PHONY : CMakeFiles/main.dir/src/crc16.c.o.provides

CMakeFiles/main.dir/src/crc16.c.o.provides.build: CMakeFiles/main.dir/src/crc16.c.o

scanner.c: ../scanner.l
	$(CMAKE_COMMAND) -E cmake_progress_report /home/grad/hmroesler/MyLittleCompiler/build/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "[FLEX][scanner] Building scanner with flex 2.5.35"
	cd /home/grad/hmroesler/MyLittleCompiler && /usr/bin/flex -o/home/grad/hmroesler/MyLittleCompiler/build/scanner.c scanner.l

parser.c: ../parser.y
	$(CMAKE_COMMAND) -E cmake_progress_report /home/grad/hmroesler/MyLittleCompiler/build/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "[BISON][parser] Building parser with bison 2.5"
	cd /home/grad/hmroesler/MyLittleCompiler && /usr/bin/bison --verbose -d -o /home/grad/hmroesler/MyLittleCompiler/build/parser.c parser.y

parser.h: parser.c

parser.output: parser.c

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/scanner.c.o" \
"CMakeFiles/main.dir/parser.c.o" \
"CMakeFiles/main.dir/src/main.c.o" \
"CMakeFiles/main.dir/src/misc.c.o" \
"CMakeFiles/main.dir/src/gv.c.o" \
"CMakeFiles/main.dir/src/comp_dict.c.o" \
"CMakeFiles/main.dir/src/comp_list.c.o" \
"CMakeFiles/main.dir/src/comp_tree.c.o" \
"CMakeFiles/main.dir/src/symbtable.c.o" \
"CMakeFiles/main.dir/src/symt.c.o" \
"CMakeFiles/main.dir/src/crc16.c.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/scanner.c.o
main: CMakeFiles/main.dir/parser.c.o
main: CMakeFiles/main.dir/src/main.c.o
main: CMakeFiles/main.dir/src/misc.c.o
main: CMakeFiles/main.dir/src/gv.c.o
main: CMakeFiles/main.dir/src/comp_dict.c.o
main: CMakeFiles/main.dir/src/comp_list.c.o
main: CMakeFiles/main.dir/src/comp_tree.c.o
main: CMakeFiles/main.dir/src/symbtable.c.o
main: CMakeFiles/main.dir/src/symt.c.o
main: CMakeFiles/main.dir/src/crc16.c.o
main: /usr/lib/x86_64-linux-gnu/libfl.so
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/requires: CMakeFiles/main.dir/scanner.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/parser.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/main.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/misc.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/gv.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/comp_dict.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/comp_list.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/comp_tree.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/symbtable.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/symt.c.o.requires
CMakeFiles/main.dir/requires: CMakeFiles/main.dir/src/crc16.c.o.requires
.PHONY : CMakeFiles/main.dir/requires

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend: scanner.c
CMakeFiles/main.dir/depend: parser.c
CMakeFiles/main.dir/depend: parser.h
CMakeFiles/main.dir/depend: parser.output
	cd /home/grad/hmroesler/MyLittleCompiler/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/grad/hmroesler/MyLittleCompiler /home/grad/hmroesler/MyLittleCompiler /home/grad/hmroesler/MyLittleCompiler/build /home/grad/hmroesler/MyLittleCompiler/build /home/grad/hmroesler/MyLittleCompiler/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

