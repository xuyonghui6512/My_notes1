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
CMAKE_SOURCE_DIR = /home/xuxuxu/b/My_notes1/条形码识别

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xuxuxu/b/My_notes1/条形码识别/cmake-build-debug

# Include any dependencies generated for this target.
include src/CMakeFiles/bar_code.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/bar_code.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/bar_code.dir/flags.make

src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o: src/CMakeFiles/bar_code.dir/flags.make
src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o: ../src/my_bar_code.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuxuxu/b/My_notes1/条形码识别/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o"
	cd /home/xuxuxu/b/My_notes1/条形码识别/cmake-build-debug/src && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bar_code.dir/my_bar_code.cpp.o -c /home/xuxuxu/b/My_notes1/条形码识别/src/my_bar_code.cpp

src/CMakeFiles/bar_code.dir/my_bar_code.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bar_code.dir/my_bar_code.cpp.i"
	cd /home/xuxuxu/b/My_notes1/条形码识别/cmake-build-debug/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuxuxu/b/My_notes1/条形码识别/src/my_bar_code.cpp > CMakeFiles/bar_code.dir/my_bar_code.cpp.i

src/CMakeFiles/bar_code.dir/my_bar_code.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bar_code.dir/my_bar_code.cpp.s"
	cd /home/xuxuxu/b/My_notes1/条形码识别/cmake-build-debug/src && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuxuxu/b/My_notes1/条形码识别/src/my_bar_code.cpp -o CMakeFiles/bar_code.dir/my_bar_code.cpp.s

src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.requires:

.PHONY : src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.requires

src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.provides: src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/bar_code.dir/build.make src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.provides.build
.PHONY : src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.provides

src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.provides.build: src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o


# Object files for target bar_code
bar_code_OBJECTS = \
"CMakeFiles/bar_code.dir/my_bar_code.cpp.o"

# External object files for target bar_code
bar_code_EXTERNAL_OBJECTS =

../lib/libbar_code.so: src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o
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
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xuxuxu/b/My_notes1/条形码识别/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ../../lib/libbar_code.so"
	cd /home/xuxuxu/b/My_notes1/条形码识别/cmake-build-debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bar_code.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/bar_code.dir/build: ../lib/libbar_code.so

.PHONY : src/CMakeFiles/bar_code.dir/build

src/CMakeFiles/bar_code.dir/requires: src/CMakeFiles/bar_code.dir/my_bar_code.cpp.o.requires

.PHONY : src/CMakeFiles/bar_code.dir/requires

src/CMakeFiles/bar_code.dir/clean:
	cd /home/xuxuxu/b/My_notes1/条形码识别/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/bar_code.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/bar_code.dir/clean

src/CMakeFiles/bar_code.dir/depend:
	cd /home/xuxuxu/b/My_notes1/条形码识别/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xuxuxu/b/My_notes1/条形码识别 /home/xuxuxu/b/My_notes1/条形码识别/src /home/xuxuxu/b/My_notes1/条形码识别/cmake-build-debug /home/xuxuxu/b/My_notes1/条形码识别/cmake-build-debug/src /home/xuxuxu/b/My_notes1/条形码识别/cmake-build-debug/src/CMakeFiles/bar_code.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/bar_code.dir/depend

