# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /snap/clion/137/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/137/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/lerakrya/Загрузки/Telegram Desktop/ServerUsers"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/lerakrya/Загрузки/Telegram Desktop/ServerUsers/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/echo_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/echo_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/echo_server.dir/flags.make

CMakeFiles/echo_server.dir/echo_server.cpp.o: CMakeFiles/echo_server.dir/flags.make
CMakeFiles/echo_server.dir/echo_server.cpp.o: ../echo_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/lerakrya/Загрузки/Telegram Desktop/ServerUsers/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/echo_server.dir/echo_server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo_server.dir/echo_server.cpp.o -c "/home/lerakrya/Загрузки/Telegram Desktop/ServerUsers/echo_server.cpp"

CMakeFiles/echo_server.dir/echo_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_server.dir/echo_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/lerakrya/Загрузки/Telegram Desktop/ServerUsers/echo_server.cpp" > CMakeFiles/echo_server.dir/echo_server.cpp.i

CMakeFiles/echo_server.dir/echo_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_server.dir/echo_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/lerakrya/Загрузки/Telegram Desktop/ServerUsers/echo_server.cpp" -o CMakeFiles/echo_server.dir/echo_server.cpp.s

# Object files for target echo_server
echo_server_OBJECTS = \
"CMakeFiles/echo_server.dir/echo_server.cpp.o"

# External object files for target echo_server
echo_server_EXTERNAL_OBJECTS =

echo_server: CMakeFiles/echo_server.dir/echo_server.cpp.o
echo_server: CMakeFiles/echo_server.dir/build.make
echo_server: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
echo_server: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
echo_server: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
echo_server: /usr/lib/x86_64-linux-gnu/libboost_log.so.1.71.0
echo_server: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
echo_server: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
echo_server: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
echo_server: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
echo_server: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.71.0
echo_server: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
echo_server: CMakeFiles/echo_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/lerakrya/Загрузки/Telegram Desktop/ServerUsers/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable echo_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/echo_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/echo_server.dir/build: echo_server

.PHONY : CMakeFiles/echo_server.dir/build

CMakeFiles/echo_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/echo_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/echo_server.dir/clean

CMakeFiles/echo_server.dir/depend:
	cd "/home/lerakrya/Загрузки/Telegram Desktop/ServerUsers/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/lerakrya/Загрузки/Telegram Desktop/ServerUsers" "/home/lerakrya/Загрузки/Telegram Desktop/ServerUsers" "/home/lerakrya/Загрузки/Telegram Desktop/ServerUsers/cmake-build-debug" "/home/lerakrya/Загрузки/Telegram Desktop/ServerUsers/cmake-build-debug" "/home/lerakrya/Загрузки/Telegram Desktop/ServerUsers/cmake-build-debug/CMakeFiles/echo_server.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/echo_server.dir/depend

