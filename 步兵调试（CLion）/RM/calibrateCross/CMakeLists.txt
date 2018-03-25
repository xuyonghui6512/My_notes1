


#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

#add_library(myVideoCap SHARED
#        ${CAP_SRC})


#target_link_libraries(myVideoCap
#        ${OpenCV_LIBS})

add_executable(calibrateCross calibrateCross.cpp
        )

target_link_libraries(calibrateCross
        -lpthread
        ${Boost_LIBRARIES}
        ${OpenCV_LIBS}
        myVideoCap
        ArmorDetect
        )
