cmake_minimum_required(VERSION 3.5)
project(multithreading)

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



add_executable(multithreading main.cpp )

target_link_libraries(multithreading
        -lpthread
        /usr/lib/x86_64-linux-gnu/libboost_system.so
        /usr/lib/x86_64-linux-gnu/libboost_thread.so
        ${BOOST_LIBRARIES}
        ${OpenCV_LIBS}
        )




