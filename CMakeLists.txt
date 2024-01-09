cmake_minimum_required(VERSION 3.5.0)
project(main VERSION 0.0.1)

set (OpenGL_GL_PREFERENCE LEGACY)

find_package(OpenGL REQUIRED)
add_executable(main
    src/main.cpp
    src/glad.c    
)

target_include_directories(main PRIVATE dependencies)
target_link_libraries(main glfw OpenGL::GL)
