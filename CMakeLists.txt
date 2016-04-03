cmake_minimum_required(VERSION 3.5)
project(raytracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/vec3.cpp src/vec3.h src/ray.cpp src/ray.h src/surface.cpp src/surface.h)
add_executable(raytracer ${SOURCE_FILES})