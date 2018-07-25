cmake_minimum_required(VERSION 3.8)
project(TestBasler)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)#Release
set(CMAKE_CONFIGURATION_TYPES Debug Release)

set(CMAKE_C_FLAGS_RELEASE  "${CMAKE_C_FLAGS_RELEASE} -Wall -O3 -march=native")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -pg -march=native")

set(CMAKE_CXX_FLAGS_RELEASE   "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3 -march=native")
set(CMAKE_CXX_FLAGS_DEBUG    "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pg -march=native")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

find_package(OpenCV 3.1.0 REQUIRED)
find_package(Boost  REQUIRED)

include_directories(
        ${OPENCV_INCLUDE_DIRS}
        #        ${Boost_INCLUDE_DIRS}
        /opt/pylon5/include
)

add_subdirectory(Camera_pylon)

set(SOURCE_FILES main.cpp)
add_executable(TestBasler ${SOURCE_FILES})

target_link_libraries(TestBasler
        ${OpenCV_LIBS}
        Camera_pylon
        /opt/pylon5/lib64/libbxapi.so
        /opt/pylon5/lib64/libbxapi-5.0.11.so
        /opt/pylon5/lib64/libFirmwareUpdate_gcc_v3_0_Basler_pylon_v5_0.so
        /opt/pylon5/lib64/libGCBase_gcc_v3_0_Basler_pylon_v5_0.so
        /opt/pylon5/lib64/libGenApi_gcc_v3_0_Basler_pylon_v5_0.so
        /opt/pylon5/lib64/libgxapi.so
        /opt/pylon5/lib64/libgxapi-5.0.11.so
        /opt/pylon5/lib64/liblog4cpp_gcc_v3_0_Basler_pylon_v5_0.so
        /opt/pylon5/lib64/libLog_gcc_v3_0_Basler_pylon_v5_0.so
        /opt/pylon5/lib64/libMathParser_gcc_v3_0_Basler_pylon_v5_0.so
        /opt/pylon5/lib64/libNodeMapData_gcc_v3_0_Basler_pylon_v5_0.so
        /opt/pylon5/lib64/libpylonbase.so
        /opt/pylon5/lib64/libpylonbase-5.0.11.so
        /opt/pylon5/lib64/libpylonc.so
        /opt/pylon5/lib64/libpylonc-5.0.11.so
        /opt/pylon5/lib64/libpylon_TL_bcon.so
        /opt/pylon5/lib64/libpylon_TL_bcon-5.0.11.so
        /opt/pylon5/lib64/libpylon_TL_camemu.so
        /opt/pylon5/lib64/libpylon_TL_camemu-5.0.11.so
        /opt/pylon5/lib64/libpylon_TL_gige.so
        /opt/pylon5/lib64/libpylon_TL_gige-5.0.11.so
        /opt/pylon5/lib64/libpylon_TL_usb.so
        /opt/pylon5/lib64/libpylon_TL_usb-5.0.11.so
        /opt/pylon5/lib64/libpylonutility.so
        /opt/pylon5/lib64/libpylonutility-5.0.11.so
        /opt/pylon5/lib64/libuxapi.so
        /opt/pylon5/lib64/libuxapi-5.0.11.so
        /opt/pylon5/lib64/libXmlParser_gcc_v3_0_Basler_pylon_v5_0.so
        /opt/pylon5/lib64/pylon-libusb-1.0.so
        )

