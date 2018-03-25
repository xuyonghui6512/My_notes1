







add_executable(testSerialSend testSerialSend.cpp
        )

target_link_libraries(testSerialSend
        -lpthread
        ${Boost_LIBRARIES}
        ${OpenCV_LIBS}
        ArmorDetect
        )