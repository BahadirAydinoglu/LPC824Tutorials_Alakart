# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/local/lib/python3.8/dist-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /usr/local/lib/python3.8/dist-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bahadira/Seafile/BahadirFiles/Firmwares/LPC824Tutorials_Alakart/UsartTx

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bahadira/Seafile/BahadirFiles/Firmwares/LPC824Tutorials_Alakart/UsartTx

# Utility rule file for CreateHex.

# Include any custom commands dependencies for this target.
include CMakeFiles/CreateHex.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CreateHex.dir/progress.make

CMakeFiles/CreateHex: release/UsartTx.elf

CreateHex: CMakeFiles/CreateHex
CreateHex: CMakeFiles/CreateHex.dir/build.make
	bash -c arm-none-eabi-objcopy\ -O\ ihex\ /home/bahadira/Seafile/BahadirFiles/Firmwares/LPC824Tutorials_Alakart/UsartTx/release/UsartTx.elf\ /home/bahadira/Seafile/BahadirFiles/Firmwares/LPC824Tutorials_Alakart/UsartTx/release/UsartTx.hex
.PHONY : CreateHex

# Rule to build all files generated by this target.
CMakeFiles/CreateHex.dir/build: CreateHex
.PHONY : CMakeFiles/CreateHex.dir/build

CMakeFiles/CreateHex.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CreateHex.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CreateHex.dir/clean

CMakeFiles/CreateHex.dir/depend:
	cd /home/bahadira/Seafile/BahadirFiles/Firmwares/LPC824Tutorials_Alakart/UsartTx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bahadira/Seafile/BahadirFiles/Firmwares/LPC824Tutorials_Alakart/UsartTx /home/bahadira/Seafile/BahadirFiles/Firmwares/LPC824Tutorials_Alakart/UsartTx /home/bahadira/Seafile/BahadirFiles/Firmwares/LPC824Tutorials_Alakart/UsartTx /home/bahadira/Seafile/BahadirFiles/Firmwares/LPC824Tutorials_Alakart/UsartTx /home/bahadira/Seafile/BahadirFiles/Firmwares/LPC824Tutorials_Alakart/UsartTx/CMakeFiles/CreateHex.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CreateHex.dir/depend

