# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/Build

# Include any dependencies generated for this target.
include CMakeFiles/textspel.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/textspel.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/textspel.dir/flags.make

CMakeFiles/textspel.dir/textspel.c.o: CMakeFiles/textspel.dir/flags.make
CMakeFiles/textspel.dir/textspel.c.o: ../textspel.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/textspel.dir/textspel.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/textspel.dir/textspel.c.o   -c /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/textspel.c

CMakeFiles/textspel.dir/textspel.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/textspel.dir/textspel.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/textspel.c > CMakeFiles/textspel.dir/textspel.c.i

CMakeFiles/textspel.dir/textspel.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/textspel.dir/textspel.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/textspel.c -o CMakeFiles/textspel.dir/textspel.c.s

CMakeFiles/textspel.dir/textspel.c.o.requires:

.PHONY : CMakeFiles/textspel.dir/textspel.c.o.requires

CMakeFiles/textspel.dir/textspel.c.o.provides: CMakeFiles/textspel.dir/textspel.c.o.requires
	$(MAKE) -f CMakeFiles/textspel.dir/build.make CMakeFiles/textspel.dir/textspel.c.o.provides.build
.PHONY : CMakeFiles/textspel.dir/textspel.c.o.provides

CMakeFiles/textspel.dir/textspel.c.o.provides.build: CMakeFiles/textspel.dir/textspel.c.o


CMakeFiles/textspel.dir/world.c.o: CMakeFiles/textspel.dir/flags.make
CMakeFiles/textspel.dir/world.c.o: ../world.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/textspel.dir/world.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/textspel.dir/world.c.o   -c /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/world.c

CMakeFiles/textspel.dir/world.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/textspel.dir/world.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/world.c > CMakeFiles/textspel.dir/world.c.i

CMakeFiles/textspel.dir/world.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/textspel.dir/world.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/world.c -o CMakeFiles/textspel.dir/world.c.s

CMakeFiles/textspel.dir/world.c.o.requires:

.PHONY : CMakeFiles/textspel.dir/world.c.o.requires

CMakeFiles/textspel.dir/world.c.o.provides: CMakeFiles/textspel.dir/world.c.o.requires
	$(MAKE) -f CMakeFiles/textspel.dir/build.make CMakeFiles/textspel.dir/world.c.o.provides.build
.PHONY : CMakeFiles/textspel.dir/world.c.o.provides

CMakeFiles/textspel.dir/world.c.o.provides.build: CMakeFiles/textspel.dir/world.c.o


CMakeFiles/textspel.dir/player.c.o: CMakeFiles/textspel.dir/flags.make
CMakeFiles/textspel.dir/player.c.o: ../player.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/textspel.dir/player.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/textspel.dir/player.c.o   -c /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/player.c

CMakeFiles/textspel.dir/player.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/textspel.dir/player.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/player.c > CMakeFiles/textspel.dir/player.c.i

CMakeFiles/textspel.dir/player.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/textspel.dir/player.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/player.c -o CMakeFiles/textspel.dir/player.c.s

CMakeFiles/textspel.dir/player.c.o.requires:

.PHONY : CMakeFiles/textspel.dir/player.c.o.requires

CMakeFiles/textspel.dir/player.c.o.provides: CMakeFiles/textspel.dir/player.c.o.requires
	$(MAKE) -f CMakeFiles/textspel.dir/build.make CMakeFiles/textspel.dir/player.c.o.provides.build
.PHONY : CMakeFiles/textspel.dir/player.c.o.provides

CMakeFiles/textspel.dir/player.c.o.provides.build: CMakeFiles/textspel.dir/player.c.o


# Object files for target textspel
textspel_OBJECTS = \
"CMakeFiles/textspel.dir/textspel.c.o" \
"CMakeFiles/textspel.dir/world.c.o" \
"CMakeFiles/textspel.dir/player.c.o"

# External object files for target textspel
textspel_EXTERNAL_OBJECTS =

textspel: CMakeFiles/textspel.dir/textspel.c.o
textspel: CMakeFiles/textspel.dir/world.c.o
textspel: CMakeFiles/textspel.dir/player.c.o
textspel: CMakeFiles/textspel.dir/build.make
textspel: CMakeFiles/textspel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable textspel"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/textspel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/textspel.dir/build: textspel

.PHONY : CMakeFiles/textspel.dir/build

CMakeFiles/textspel.dir/requires: CMakeFiles/textspel.dir/textspel.c.o.requires
CMakeFiles/textspel.dir/requires: CMakeFiles/textspel.dir/world.c.o.requires
CMakeFiles/textspel.dir/requires: CMakeFiles/textspel.dir/player.c.o.requires

.PHONY : CMakeFiles/textspel.dir/requires

CMakeFiles/textspel.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/textspel.dir/cmake_clean.cmake
.PHONY : CMakeFiles/textspel.dir/clean

CMakeFiles/textspel.dir/depend:
	cd /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/Build /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/Build /home/EDUNET.ORU.SE/delyoh211/Desktop/Spel/Build/CMakeFiles/textspel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/textspel.dir/depend

