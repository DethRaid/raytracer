cmake_minimum_required(VERSION 3.5)
project(raytracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/vec3.cpp src/vec3.h src/ray.cpp src/ray.h src/surfaces/surface.cpp src/surfaces/surface.h src/surfaces/sphere.cpp src/surfaces/sphere.h src/scene.cpp src/scene.h src/camera.cpp src/camera.h)
add_executable(raytracer ${SOURCE_FILES})