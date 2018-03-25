
set(ARMOR_DETECT_SRC
        Armor.cpp
        Armor.h
        ArmorDetect.cpp
        ArmorDetect.h
        Param.cpp
        Param.h
        Predictor.cpp
        Predictor.h
        serialbase.h
        serialbase.cpp
        serialapp.h
        serialapp.cpp)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_library(ArmorDetect SHARED
        ${ARMOR_DETECT_SRC}
        )


target_link_libraries(ArmorDetect
        ${OpenCV_LIBS}
        /usr/lib/x86_64-linux-gnu/libboost_system.so
        /usr/lib/x86_64-linux-gnu/libboost_thread.so)


