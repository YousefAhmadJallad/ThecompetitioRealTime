cmake_minimum_required(VERSION 3.10.0)
project(my_opengl_project1 VERSION 0.1.0)

cmake_policy(SET CMP0070 NEW)

find_package(OpenGL REQUIRED)

add_executable(my_opengl_project1 parent.c )


target_link_libraries(my_opengl_project1 glfw)