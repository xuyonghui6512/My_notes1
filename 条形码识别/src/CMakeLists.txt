add_library( bar_code SHARED
my_bar_code.cpp)

target_link_libraries( bar_code
    ${NEEDED_LIBS}
)
