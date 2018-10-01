cmake_minimum_required(VERSION 3.12)
project(danmaku)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp -O3")
link_libraries(glfw3 gdi32 opengl32)
add_executable(danmaku main.cpp window.h danmaku.h particle.h)