# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/xuxuxu/clion-2017.3.4/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/xuxuxu/clion-2017.3.4/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug"

# Include any dependencies generated for this target.
include src/CMakeFiles/bar_code.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/bar_code.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/bar_code.dir/flags.make

src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o: src/CMakeFiles/bar_code.dir/flags.make
src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o: ../src/my_bar_code.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bar_code.dir/my_bar_code.cpp.o -c "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/my_bar_code.cpp"

src/CMakeFiles/bar_code.dir/my_bar_code.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bar_code.dir/my_bar_code.cpp.i"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/my_bar_code.cpp" > CMakeFiles/bar_code.dir/my_bar_code.cpp.i

src/CMakeFiles/bar_code.dir/my_bar_code.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bar_code.dir/my_bar_code.cpp.s"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/my_bar_code.cpp" -o CMakeFiles/bar_code.dir/my_bar_code.cpp.s

src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.requires:

.PHONY : src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.requires

src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.provides: src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/bar_code.dir/build.make src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.provides.build
.PHONY : src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.provides

src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.provides.build: src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o


src/CMakeFiles/bar_code.dir/find_and_pick.cpp.o: src/CMakeFiles/bar_code.dir/flags.make
src/CMakeFiles/bar_code.dir/find_and_pick.cpp.o: ../src/find_and_pick.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/bar_code.dir/find_and_pick.cpp.o"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bar_code.dir/find_and_pick.cpp.o -c "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/find_and_pick.cpp"

src/CMakeFiles/bar_code.dir/find_and_pick.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bar_code.dir/find_and_pick.cpp.i"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/find_and_pick.cpp" > CMakeFiles/bar_code.dir/find_and_pick.cpp.i

src/CMakeFiles/bar_code.dir/find_and_pick.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bar_code.dir/find_and_pick.cpp.s"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/find_and_pick.cpp" -o CMakeFiles/bar_code.dir/find_and_pick.cpp.s

src/CMakeFiles/bar_code.dir/find_and_pick.cpp.o.requires:

.PHONY : src/CMakeFiles/bar_code.dir/find_and_pick.cpp.o.requires

src/CMakeFiles/bar_code.dir/find_and_pick.cpp.o.provides: src/CMakeFiles/bar_code.dir/find_and_pick.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/bar_code.dir/build.make src/CMakeFiles/bar_code.dir/find_and_pick.cpp.o.provides.build
.PHONY : src/CMakeFiles/bar_code.dir/find_and_pick.cpp.o.provides

src/CMakeFiles/bar_code.dir/find_and_pick.cpp.o.provides.build: src/CMakeFiles/bar_code.dir/find_and_pick.cpp.o


src/CMakeFiles/bar_code.dir/image_handle.cpp.o: src/CMakeFiles/bar_code.dir/flags.make
src/CMakeFiles/bar_code.dir/image_handle.cpp.o: ../src/image_handle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/bar_code.dir/image_handle.cpp.o"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bar_code.dir/image_handle.cpp.o -c "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/image_handle.cpp"

src/CMakeFiles/bar_code.dir/image_handle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bar_code.dir/image_handle.cpp.i"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/image_handle.cpp" > CMakeFiles/bar_code.dir/image_handle.cpp.i

src/CMakeFiles/bar_code.dir/image_handle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bar_code.dir/image_handle.cpp.s"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/image_handle.cpp" -o CMakeFiles/bar_code.dir/image_handle.cpp.s

src/CMakeFiles/bar_code.dir/image_handle.cpp.o.requires:

.PHONY : src/CMakeFiles/bar_code.dir/image_handle.cpp.o.requires

src/CMakeFiles/bar_code.dir/image_handle.cpp.o.provides: src/CMakeFiles/bar_code.dir/image_handle.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/bar_code.dir/build.make src/CMakeFiles/bar_code.dir/image_handle.cpp.o.provides.build
.PHONY : src/CMakeFiles/bar_code.dir/image_handle.cpp.o.provides

src/CMakeFiles/bar_code.dir/image_handle.cpp.o.provides.build: src/CMakeFiles/bar_code.dir/image_handle.cpp.o


src/CMakeFiles/bar_code.dir/myVideoCap.cpp.o: src/CMakeFiles/bar_code.dir/flags.make
src/CMakeFiles/bar_code.dir/myVideoCap.cpp.o: ../src/myVideoCap.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/bar_code.dir/myVideoCap.cpp.o"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bar_code.dir/myVideoCap.cpp.o -c "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/myVideoCap.cpp"

src/CMakeFiles/bar_code.dir/myVideoCap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bar_code.dir/myVideoCap.cpp.i"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/myVideoCap.cpp" > CMakeFiles/bar_code.dir/myVideoCap.cpp.i

src/CMakeFiles/bar_code.dir/myVideoCap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bar_code.dir/myVideoCap.cpp.s"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/myVideoCap.cpp" -o CMakeFiles/bar_code.dir/myVideoCap.cpp.s

src/CMakeFiles/bar_code.dir/myVideoCap.cpp.o.requires:

.PHONY : src/CMakeFiles/bar_code.dir/myVideoCap.cpp.o.requires

src/CMakeFiles/bar_code.dir/myVideoCap.cpp.o.provides: src/CMakeFiles/bar_code.dir/myVideoCap.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/bar_code.dir/build.make src/CMakeFiles/bar_code.dir/myVideoCap.cpp.o.provides.build
.PHONY : src/CMakeFiles/bar_code.dir/myVideoCap.cpp.o.provides

src/CMakeFiles/bar_code.dir/myVideoCap.cpp.o.provides.build: src/CMakeFiles/bar_code.dir/myVideoCap.cpp.o


src/CMakeFiles/bar_code.dir/v4l2uvc.c.o: src/CMakeFiles/bar_code.dir/flags.make
src/CMakeFiles/bar_code.dir/v4l2uvc.c.o: ../src/v4l2uvc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/CMakeFiles/bar_code.dir/v4l2uvc.c.o"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/bar_code.dir/v4l2uvc.c.o   -c "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/v4l2uvc.c"

src/CMakeFiles/bar_code.dir/v4l2uvc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bar_code.dir/v4l2uvc.c.i"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/v4l2uvc.c" > CMakeFiles/bar_code.dir/v4l2uvc.c.i

src/CMakeFiles/bar_code.dir/v4l2uvc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bar_code.dir/v4l2uvc.c.s"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/v4l2uvc.c" -o CMakeFiles/bar_code.dir/v4l2uvc.c.s

src/CMakeFiles/bar_code.dir/v4l2uvc.c.o.requires:

.PHONY : src/CMakeFiles/bar_code.dir/v4l2uvc.c.o.requires

src/CMakeFiles/bar_code.dir/v4l2uvc.c.o.provides: src/CMakeFiles/bar_code.dir/v4l2uvc.c.o.requires
	$(MAKE) -f src/CMakeFiles/bar_code.dir/build.make src/CMakeFiles/bar_code.dir/v4l2uvc.c.o.provides.build
.PHONY : src/CMakeFiles/bar_code.dir/v4l2uvc.c.o.provides

src/CMakeFiles/bar_code.dir/v4l2uvc.c.o.provides.build: src/CMakeFiles/bar_code.dir/v4l2uvc.c.o


src/CMakeFiles/bar_code.dir/serialapp.cpp.o: src/CMakeFiles/bar_code.dir/flags.make
src/CMakeFiles/bar_code.dir/serialapp.cpp.o: ../src/serialapp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/bar_code.dir/serialapp.cpp.o"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bar_code.dir/serialapp.cpp.o -c "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/serialapp.cpp"

src/CMakeFiles/bar_code.dir/serialapp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bar_code.dir/serialapp.cpp.i"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/serialapp.cpp" > CMakeFiles/bar_code.dir/serialapp.cpp.i

src/CMakeFiles/bar_code.dir/serialapp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bar_code.dir/serialapp.cpp.s"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/serialapp.cpp" -o CMakeFiles/bar_code.dir/serialapp.cpp.s

src/CMakeFiles/bar_code.dir/serialapp.cpp.o.requires:

.PHONY : src/CMakeFiles/bar_code.dir/serialapp.cpp.o.requires

src/CMakeFiles/bar_code.dir/serialapp.cpp.o.provides: src/CMakeFiles/bar_code.dir/serialapp.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/bar_code.dir/build.make src/CMakeFiles/bar_code.dir/serialapp.cpp.o.provides.build
.PHONY : src/CMakeFiles/bar_code.dir/serialapp.cpp.o.provides

src/CMakeFiles/bar_code.dir/serialapp.cpp.o.provides.build: src/CMakeFiles/bar_code.dir/serialapp.cpp.o


src/CMakeFiles/bar_code.dir/serialbase.cpp.o: src/CMakeFiles/bar_code.dir/flags.make
src/CMakeFiles/bar_code.dir/serialbase.cpp.o: ../src/serialbase.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/bar_code.dir/serialbase.cpp.o"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bar_code.dir/serialbase.cpp.o -c "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/serialbase.cpp"

src/CMakeFiles/bar_code.dir/serialbase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bar_code.dir/serialbase.cpp.i"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/serialbase.cpp" > CMakeFiles/bar_code.dir/serialbase.cpp.i

src/CMakeFiles/bar_code.dir/serialbase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bar_code.dir/serialbase.cpp.s"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src/serialbase.cpp" -o CMakeFiles/bar_code.dir/serialbase.cpp.s

src/CMakeFiles/bar_code.dir/serialbase.cpp.o.requires:

.PHONY : src/CMakeFiles/bar_code.dir/serialbase.cpp.o.requires

src/CMakeFiles/bar_code.dir/serialbase.cpp.o.provides: src/CMakeFiles/bar_code.dir/serialbase.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/bar_code.dir/build.make src/CMakeFiles/bar_code.dir/serialbase.cpp.o.provides.build
.PHONY : src/CMakeFiles/bar_code.dir/serialbase.cpp.o.provides

src/CMakeFiles/bar_code.dir/serialbase.cpp.o.provides.build: src/CMakeFiles/bar_code.dir/serialbase.cpp.o


# Object files for target bar_code
bar_code_OBJECTS = \
"CMakeFiles/bar_code.dir/my_bar_code.cpp.o" \
"CMakeFiles/bar_code.dir/find_and_pick.cpp.o" \
"CMakeFiles/bar_code.dir/image_handle.cpp.o" \
"CMakeFiles/bar_code.dir/myVideoCap.cpp.o" \
"CMakeFiles/bar_code.dir/v4l2uvc.c.o" \
"CMakeFiles/bar_code.dir/serialapp.cpp.o" \
"CMakeFiles/bar_code.dir/serialbase.cpp.o"

# External object files for target bar_code
bar_code_EXTERNAL_OBJECTS =

../lib/libbar_code.so: src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o
../lib/libbar_code.so: src/CMakeFiles/bar_code.dir/find_and_pick.cpp.o
../lib/libbar_code.so: src/CMakeFiles/bar_code.dir/image_handle.cpp.o
../lib/libbar_code.so: src/CMakeFiles/bar_code.dir/myVideoCap.cpp.o
../lib/libbar_code.so: src/CMakeFiles/bar_code.dir/v4l2uvc.c.o
../lib/libbar_code.so: src/CMakeFiles/bar_code.dir/serialapp.cpp.o
../lib/libbar_code.so: src/CMakeFiles/bar_code.dir/serialbase.cpp.o
../lib/libbar_code.so: src/CMakeFiles/bar_code.dir/build.make
../lib/libbar_code.so: /usr/local/lib/libopencv_stitching.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_superres.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_videostab.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_aruco.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_bgsegm.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_bioinspired.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_ccalib.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_dpm.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_freetype.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_fuzzy.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_line_descriptor.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_optflow.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_reg.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_saliency.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_stereo.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_structured_light.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_surface_matching.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_tracking.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_xfeatures2d.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_ximgproc.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_xobjdetect.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_xphoto.so.3.2.0
../lib/libbar_code.so: /usr/lib/x86_64-linux-gnu/libboost_system.so
../lib/libbar_code.so: /usr/lib/x86_64-linux-gnu/libboost_thread.so
../lib/libbar_code.so: /opt/pylon5/lib64/libbxapi.so
../lib/libbar_code.so: /opt/pylon5/lib64/libbxapi-5.0.11.so
../lib/libbar_code.so: /opt/pylon5/lib64/libFirmwareUpdate_gcc_v3_0_Basler_pylon_v5_0.so
../lib/libbar_code.so: /opt/pylon5/lib64/libGCBase_gcc_v3_0_Basler_pylon_v5_0.so
../lib/libbar_code.so: /opt/pylon5/lib64/libGenApi_gcc_v3_0_Basler_pylon_v5_0.so
../lib/libbar_code.so: /opt/pylon5/lib64/libgxapi.so
../lib/libbar_code.so: /opt/pylon5/lib64/libgxapi-5.0.11.so
../lib/libbar_code.so: /opt/pylon5/lib64/liblog4cpp_gcc_v3_0_Basler_pylon_v5_0.so
../lib/libbar_code.so: /opt/pylon5/lib64/libLog_gcc_v3_0_Basler_pylon_v5_0.so
../lib/libbar_code.so: /opt/pylon5/lib64/libMathParser_gcc_v3_0_Basler_pylon_v5_0.so
../lib/libbar_code.so: /opt/pylon5/lib64/libNodeMapData_gcc_v3_0_Basler_pylon_v5_0.so
../lib/libbar_code.so: /opt/pylon5/lib64/libpylonbase.so
../lib/libbar_code.so: /opt/pylon5/lib64/libpylonbase-5.0.11.so
../lib/libbar_code.so: /opt/pylon5/lib64/libpylonc.so
../lib/libbar_code.so: /opt/pylon5/lib64/libpylonc-5.0.11.so
../lib/libbar_code.so: /opt/pylon5/lib64/libpylon_TL_bcon.so
../lib/libbar_code.so: /opt/pylon5/lib64/libpylon_TL_bcon-5.0.11.so
../lib/libbar_code.so: /opt/pylon5/lib64/libpylon_TL_camemu.so
../lib/libbar_code.so: /opt/pylon5/lib64/libpylon_TL_camemu-5.0.11.so
../lib/libbar_code.so: /opt/pylon5/lib64/libpylon_TL_gige.so
../lib/libbar_code.so: /opt/pylon5/lib64/libpylon_TL_gige-5.0.11.so
../lib/libbar_code.so: /opt/pylon5/lib64/libpylon_TL_usb.so
../lib/libbar_code.so: /opt/pylon5/lib64/libpylon_TL_usb-5.0.11.so
../lib/libbar_code.so: /opt/pylon5/lib64/libpylonutility.so
../lib/libbar_code.so: /opt/pylon5/lib64/libpylonutility-5.0.11.so
../lib/libbar_code.so: /opt/pylon5/lib64/libuxapi.so
../lib/libbar_code.so: /opt/pylon5/lib64/libuxapi-5.0.11.so
../lib/libbar_code.so: /opt/pylon5/lib64/libXmlParser_gcc_v3_0_Basler_pylon_v5_0.so
../lib/libbar_code.so: /opt/pylon5/lib64/pylon-libusb-1.0.so
../lib/libbar_code.so: /usr/local/lib/libopencv_shape.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_phase_unwrapping.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_rgbd.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_calib3d.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_video.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_datasets.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_dnn.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_face.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_plot.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_text.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_features2d.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_flann.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_objdetect.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_ml.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_highgui.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_photo.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_videoio.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_imgproc.so.3.2.0
../lib/libbar_code.so: /usr/local/lib/libopencv_core.so.3.2.0
../lib/libbar_code.so: src/CMakeFiles/bar_code.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX shared library ../../lib/libbar_code.so"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bar_code.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/bar_code.dir/build: ../lib/libbar_code.so

.PHONY : src/CMakeFiles/bar_code.dir/build

src/CMakeFiles/bar_code.dir/requires: src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.requires
src/CMakeFiles/bar_code.dir/requires: src/CMakeFiles/bar_code.dir/find_and_pick.cpp.o.requires
src/CMakeFiles/bar_code.dir/requires: src/CMakeFiles/bar_code.dir/image_handle.cpp.o.requires
src/CMakeFiles/bar_code.dir/requires: src/CMakeFiles/bar_code.dir/myVideoCap.cpp.o.requires
src/CMakeFiles/bar_code.dir/requires: src/CMakeFiles/bar_code.dir/v4l2uvc.c.o.requires
src/CMakeFiles/bar_code.dir/requires: src/CMakeFiles/bar_code.dir/serialapp.cpp.o.requires
src/CMakeFiles/bar_code.dir/requires: src/CMakeFiles/bar_code.dir/serialbase.cpp.o.requires

.PHONY : src/CMakeFiles/bar_code.dir/requires

src/CMakeFiles/bar_code.dir/clean:
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" && $(CMAKE_COMMAND) -P CMakeFiles/bar_code.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/bar_code.dir/clean

src/CMakeFiles/bar_code.dir/depend:
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)" "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/src" "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug" "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src" "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版)/cmake-build-debug/src/CMakeFiles/bar_code.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/CMakeFiles/bar_code.dir/depend

