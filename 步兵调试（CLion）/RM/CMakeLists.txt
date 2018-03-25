cmake_minimum_required(VERSION 3.5)
project(RM)

set(CMAKE_CXX_STANDARD 11)


SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

set(CMAKE_BUILD_TYPE Release)

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
        ${Boost_INCLUDE_DIRS}
)

#add_definitions(-D_DEBUG)
add_subdirectory(capset)
add_subdirectory(ArmorDetect)
add_subdirectory(calibrateCross)
add_subdirectory(testSerialSend)

#set(SOURCE_FILES ArmorDetect/ArmorDetect.cpp ArmorDetect/ArmorDetect.h
#        ArmorDetect/Armor.cpp ArmorDetect/Armor.h
#        ArmorDetect/Param.cpp ArmorDetect/Param.h
#        ArmorDetect/Predictor.cpp ArmorDetect/Predictor.h
#        ArmorDetect/serialapp.cpp ArmorDetect/serialapp.h
#        ArmorDetect/serialbase.cpp ArmorDetect/serialbase.h)
add_executable(RM main.cpp )

target_link_libraries(RM
        -lpthread
        /usr/lib/x86_64-linux-gnu/libboost_system.so
        /usr/lib/x86_64-linux-gnu/libboost_thread.so
        ${BOOST_LIBRARIES}
        ${OpenCV_LIBS}
        myVideoCap
        ArmorDetect
        )



add_executable(calibration calibration/calibration.cpp)
target_link_libraries(calibration
        -lpthread
        ${BOOST_LIBS}
        ${OpenCV_LIBS}
        )

add_executable(filewrite FileWrite/filewrite.cpp)
target_link_libraries(filewrite
        -lpthread
        ${BOOST_LIBS}
        ${OpenCV_LIBS}
        )


add_executable(formal formal.cpp)
target_link_libraries(formal
        -lpthread
        /usr/lib/x86_64-linux-gnu/libboost_system.so
        /usr/lib/x86_64-linux-gnu/libboost_thread.so
        ${OpenCV_LIBS}
        ArmorDetect
        myVideoCap
        )


