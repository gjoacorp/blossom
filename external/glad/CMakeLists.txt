cmake_minimum_required(VERSION 3.10)

add_library(glad
    src/gl.c
)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(glad PROPERTIES
    LINKER_LANGUAGE C
)
