add_library( bar_code SHARED
my_bar_code.cpp
find_and_pick.cpp        )

target_link_libraries( bar_code
    ${NEEDED_LIBS}
)
