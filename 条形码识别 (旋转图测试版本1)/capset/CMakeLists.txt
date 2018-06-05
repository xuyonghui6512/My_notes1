
set(CAP_SRC
        myVideoCap.cpp
        myVideoCap.h
        v4l2uvc.h
        v4l2uvc.c)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_library(myVideoCap SHARED
        ${CAP_SRC})


target_link_libraries(myVideoCap
        ${OpenCV_LIBS})

add_executable(capset capset.cpp
        )

target_link_libraries(capset
        -lpthread
        ${Boost_LIBRARIES}
        ${OpenCV_LIBS}
        myVideoCap
        )