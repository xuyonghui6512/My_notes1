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
CMAKE_SOURCE_DIR = "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/cmake-build-debug"

# Include any dependencies generated for this target.
include test/CMakeFiles/run_test.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/run_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/run_test.dir/flags.make

test/CMakeFiles/run_test.dir/basler_video_test.cpp.o: test/CMakeFiles/run_test.dir/flags.make
test/CMakeFiles/run_test.dir/basler_video_test.cpp.o: ../test/basler_video_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/run_test.dir/basler_video_test.cpp.o"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/cmake-build-debug/test" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run_test.dir/basler_video_test.cpp.o -c "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/test/basler_video_test.cpp"

test/CMakeFiles/run_test.dir/basler_video_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run_test.dir/basler_video_test.cpp.i"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/cmake-build-debug/test" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/test/basler_video_test.cpp" > CMakeFiles/run_test.dir/basler_video_test.cpp.i

test/CMakeFiles/run_test.dir/basler_video_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run_test.dir/basler_video_test.cpp.s"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/cmake-build-debug/test" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/test/basler_video_test.cpp" -o CMakeFiles/run_test.dir/basler_video_test.cpp.s

test/CMakeFiles/run_test.dir/basler_video_test.cpp.o.requires:

.PHONY : test/CMakeFiles/run_test.dir/basler_video_test.cpp.o.requires

test/CMakeFiles/run_test.dir/basler_video_test.cpp.o.provides: test/CMakeFiles/run_test.dir/basler_video_test.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/run_test.dir/build.make test/CMakeFiles/run_test.dir/basler_video_test.cpp.o.provides.build
.PHONY : test/CMakeFiles/run_test.dir/basler_video_test.cpp.o.provides

test/CMakeFiles/run_test.dir/basler_video_test.cpp.o.provides.build: test/CMakeFiles/run_test.dir/basler_video_test.cpp.o


# Object files for target run_test
run_test_OBJECTS = \
"CMakeFiles/run_test.dir/basler_video_test.cpp.o"

# External object files for target run_test
run_test_EXTERNAL_OBJECTS =

../bin/run_test: test/CMakeFiles/run_test.dir/basler_video_test.cpp.o
../bin/run_test: test/CMakeFiles/run_test.dir/build.make
../bin/run_test: ../lib/libbar_code.so
../bin/run_test: /usr/local/lib/libopencv_stitching.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_superres.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_videostab.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_aruco.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_bgsegm.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_bioinspired.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_ccalib.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_dpm.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_freetype.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_fuzzy.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_line_descriptor.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_optflow.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_reg.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_saliency.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_stereo.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_structured_light.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_phase_unwrapping.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_rgbd.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_surface_matching.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_tracking.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_datasets.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_dnn.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_face.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_plot.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_text.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_xfeatures2d.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_shape.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_video.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_ximgproc.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_calib3d.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_features2d.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_flann.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_xobjdetect.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_objdetect.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_ml.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_xphoto.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_highgui.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_photo.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_videoio.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_imgproc.so.3.2.0
../bin/run_test: /usr/local/lib/libopencv_core.so.3.2.0
../bin/run_test: /usr/lib/x86_64-linux-gnu/libboost_system.so
../bin/run_test: /usr/lib/x86_64-linux-gnu/libboost_thread.so
../bin/run_test: /opt/pylon5/lib64/libbxapi.so
../bin/run_test: /opt/pylon5/lib64/libbxapi-5.0.11.so
../bin/run_test: /opt/pylon5/lib64/libFirmwareUpdate_gcc_v3_0_Basler_pylon_v5_0.so
../bin/run_test: /opt/pylon5/lib64/libGCBase_gcc_v3_0_Basler_pylon_v5_0.so
../bin/run_test: /opt/pylon5/lib64/libGenApi_gcc_v3_0_Basler_pylon_v5_0.so
../bin/run_test: /opt/pylon5/lib64/libgxapi.so
../bin/run_test: /opt/pylon5/lib64/libgxapi-5.0.11.so
../bin/run_test: /opt/pylon5/lib64/liblog4cpp_gcc_v3_0_Basler_pylon_v5_0.so
../bin/run_test: /opt/pylon5/lib64/libLog_gcc_v3_0_Basler_pylon_v5_0.so
../bin/run_test: /opt/pylon5/lib64/libMathParser_gcc_v3_0_Basler_pylon_v5_0.so
../bin/run_test: /opt/pylon5/lib64/libNodeMapData_gcc_v3_0_Basler_pylon_v5_0.so
../bin/run_test: /opt/pylon5/lib64/libpylonbase.so
../bin/run_test: /opt/pylon5/lib64/libpylonbase-5.0.11.so
../bin/run_test: /opt/pylon5/lib64/libpylonc.so
../bin/run_test: /opt/pylon5/lib64/libpylonc-5.0.11.so
../bin/run_test: /opt/pylon5/lib64/libpylon_TL_bcon.so
../bin/run_test: /opt/pylon5/lib64/libpylon_TL_bcon-5.0.11.so
../bin/run_test: /opt/pylon5/lib64/libpylon_TL_camemu.so
../bin/run_test: /opt/pylon5/lib64/libpylon_TL_camemu-5.0.11.so
../bin/run_test: /opt/pylon5/lib64/libpylon_TL_gige.so
../bin/run_test: /opt/pylon5/lib64/libpylon_TL_gige-5.0.11.so
../bin/run_test: /opt/pylon5/lib64/libpylon_TL_usb.so
../bin/run_test: /opt/pylon5/lib64/libpylon_TL_usb-5.0.11.so
../bin/run_test: /opt/pylon5/lib64/libpylonutility.so
../bin/run_test: /opt/pylon5/lib64/libpylonutility-5.0.11.so
../bin/run_test: /opt/pylon5/lib64/libuxapi.so
../bin/run_test: /opt/pylon5/lib64/libuxapi-5.0.11.so
../bin/run_test: /opt/pylon5/lib64/libXmlParser_gcc_v3_0_Basler_pylon_v5_0.so
../bin/run_test: /opt/pylon5/lib64/pylon-libusb-1.0.so
../bin/run_test: test/CMakeFiles/run_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/run_test"
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/cmake-build-debug/test" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/run_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/run_test.dir/build: ../bin/run_test

.PHONY : test/CMakeFiles/run_test.dir/build

test/CMakeFiles/run_test.dir/requires: test/CMakeFiles/run_test.dir/basler_video_test.cpp.o.requires

.PHONY : test/CMakeFiles/run_test.dir/requires

test/CMakeFiles/run_test.dir/clean:
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/cmake-build-debug/test" && $(CMAKE_COMMAND) -P CMakeFiles/run_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/run_test.dir/clean

test/CMakeFiles/run_test.dir/depend:
	cd "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)" "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/test" "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/cmake-build-debug" "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/cmake-build-debug/test" "/home/xuxuxu/b/My_notes1/条形码识别 (简洁版) (复件)/cmake-build-debug/test/CMakeFiles/run_test.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : test/CMakeFiles/run_test.dir/depend

