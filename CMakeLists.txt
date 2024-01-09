cmake_minimum_required(VERSION 3.5.0)
project(helloworld VERSION 0.0.1)

set (OpenGL_GL_PREFERENCE LEGACY)

find_package(OpenGL REQUIRED)
add_executable(helloworld
    src/main.cpp
    src/glad.c    
)

target_include_directories(helloworld PRIVATE dependencies)
target_link_libraries(helloworld glfw OpenGL::GL)