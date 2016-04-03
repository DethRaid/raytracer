cmake_minimum_required(VERSION 3.5)
project(raytracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/vec3.h src/ray.h src/surfaces/surface.cpp src/surfaces/surface.h src/surfaces/sphere.cpp src/surfaces/sphere.h src/scene.cpp src/scene.h src/camera.cpp src/camera.h src/materials/material.h src/materials/lambertian.cpp src/materials/lambertian.h src/utils.h src/materials/metal.cpp src/materials/metal.h src/utils.cpp src/materials/dialectric.cpp src/materials/dialectric.h src/materials/pbr_material.cpp src/materials/pbr_material.h)
add_executable(raytracer ${SOURCE_FILES})