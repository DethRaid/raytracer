cmake_minimum_required(VERSION 3.5)
project(raytracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/main.cpp
        src/vec3.h
        src/ray.h
        src/surfaces/hitable.h
        src/surfaces/sphere.cpp src/surfaces/sphere.h
        src/scene.cpp src/scene.h
        src/camera.cpp src/camera.h
        src/materials/material.h
        src/materials/lambertian.cpp
        src/materials/lambertian.h
        src/utils.h
        src/materials/metal.cpp src/materials/metal.h
        src/utils.cpp
        src/materials/dialectric.cpp src/materials/dialectric.h
        src/materials/pbr_material.cpp src/materials/pbr_material.h
        src/bvh/aabb.cpp src/bvh/aabb.h
        src/bvh/bvh_node.cpp src/bvh/bvh_node.h
        src/materials/textures/texture.h
        src/materials/textures/constant_texture.h
        src/materials/checker_texture.cpp src/materials/checker_texture.h
        src/materials/textures/perlin.cpp src/materials/textures/perlin.h
        src/materials/textures/noise_texture.h
        src/materials/textures/image_texture.cpp src/materials/textures/image_texture.h
        src/vec3.h)

add_executable(raytracer ${SOURCE_FILES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY C:/Users/David/Documents/raytracer/build/bin)