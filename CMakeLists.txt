cmake_minimum_required(VERSION 3.5)
project(raytracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/main.cpp src/ray.cpp src/ray.h src/hitables/hitable.h src/hitables/sphere.cpp src/hitables/sphere.h src/hitables/hitable_list.cpp src/hitables/hitable_list.h src/camera.cpp src/camera.h)

add_executable(raytracer ${SOURCE_FILES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY C:/Users/David/Documents/raytracer/build/bin)