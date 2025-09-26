cmake_minimum_required(VERSION 3.10)
project(blossom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES src/window.cpp src/shader.cpp src/camera.cpp src/mesh.cpp)

add_custom_target(copy_shaders ALL
   COMMAND ${CMAKE_COMMAND} -E copy_directory
   ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/shaders
   COMMENT "Copying shaders to build directory"
)

function(add_example name)
    add_executable(${name} ${SOURCES} examples/${name}.cpp)
    add_dependencies(${name} copy_shaders)
    target_include_directories(${name} PRIVATE include)
    target_link_libraries(${name} PRIVATE OpenGL::GL glfw GLEW::GLEW)
endfunction()

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_example(multi_cube)
add_example(triangle)
add_example(waves)
add_example(fullscreen_rectangle)
add_example(rectangle_camera)
add_example(view)

find_package(GTest REQUIRED)
set(TEST_SOURCES
    tests/mesh_test.cpp
)

add_executable(run_tests ${SOURCES} ${TEST_SOURCES})

target_include_directories(run_tests PRIVATE include)

target_link_libraries(run_tests
    PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
        GTest::gtest
        GTest::gtest_main
)

enable_testing()
add_test(NAME mesh_tests COMMAND run_tests)
