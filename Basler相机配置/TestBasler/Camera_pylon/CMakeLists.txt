
set(Camera_pylon
        camera_pylon.cpp
        camera_pylon.h)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_library(Camera_pylon SHARED
        ${Camera_pylon}
        )

target_link_libraries(Camera_pylon
        ${OpenCV_LIBS}
        /usr/lib/x86_64-linux-gnu/libboost_system.so
        /usr/lib/x86_64-linux-gnu/libboost_thread.so
        -lpthread
        ${Boost_LIBRARIES}

        )


