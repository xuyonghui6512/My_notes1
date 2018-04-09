cmake_minimum_required( VERSION 2.8 )
project ( bar_code )

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


############### dependencies ######################
# OpenCV
find_package( OpenCV 3.1 REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )
#boost
find_package(Boost  REQUIRED)

include_directories(
        ${Boost_INCLUDE_DIRS}
)

set( NEEDED_LIBS                              ####src's CMakeLists.txt need it
    ${OpenCV_LIBS}
    ${ZBAR_LIBRARIES} zbar
        ${BOOST_LIBRARIES}
        -lpthread
        /usr/lib/x86_64-linux-gnu/libboost_system.so
        /usr/lib/x86_64-linux-gnu/libboost_thread.so
)
############### dependencies ######################
include_directories( ${PROJECT_SOURCE_DIR}/include )
#include_directories( ${PROJECT_SOURCE_DIR}/capset )
add_subdirectory( src )
add_subdirectory( test )
#add_subdirectory(capset)

