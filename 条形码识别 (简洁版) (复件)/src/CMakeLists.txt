add_library( bar_code SHARED
my_bar_code.cpp
find_and_pick.cpp
image_handle.cpp
myVideoCap.cpp
v4l2uvc.c
)

target_link_libraries( bar_code
    ${NEEDED_LIBS}
)
