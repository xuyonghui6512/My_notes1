cmake_minimum_required( VERSION 2.8 )
project ( pcl_view )

set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -march=native -O3" )

list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )
set( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib )

############### dependencies ######################
# OpenCV
find_package( OpenCV 3.1 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
find_package(PCL 1.2 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
include_directories( "/usr/include/eigen3" )

set( NEEDED_LIBS                              ####src's CMakeLists.txt need it
    ${OpenCV_LIBS}
     ${PCL_LIBRARIES}
)
############### dependencies ######################
include_directories( ${PROJECT_SOURCE_DIR}/include )
add_subdirectory( src )
add_subdirectory( test )
