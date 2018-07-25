add_library( pcl_view SHARED
        GetVectorN.cpp ../include/GetVectorN.h ../include/Get3Points.h Get3Points.cpp)

target_link_libraries( pcl_view
    ${NEEDED_LIBS}
)
