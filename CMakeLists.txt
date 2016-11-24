cmake_minimum_required(VERSION 3.5)
project(raytracer)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/3rdparty/glm)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/3rdparty/glfw)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_LIST_DIR}/src/3rdparty/glad/include)

set(SOURCE_FILES
        src/main.cpp src/ray.h src/hitables/hitable.h src/hitables/sphere.cpp src/hitables/sphere.h
        src/camera.h src/materials/material.h
        src/materials/lambertian.h src/utils.h src/materials/metal.h src/materials/dialectric.h
        src/gl/output_window.cpp src/gl/output_window.h
        src/3rdparty/glad/src/glad.c src/hitables/moving_sphere.h src/bvh/aabb.h src/hitables/bvh_node.h src/hitables/bvh_node.cpp src/utils.cpp src/gl/wireframe_renderer.cpp src/gl/wireframe_renderer.h src/bvh/aabb.cpp src/hitables/moving_sphere.cpp src/camera.cpp)

add_executable(raytracer ${SOURCE_FILES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY C:/Users/David/Documents/raytracer/build/bin)

add_dependencies(raytracer glfw3)
target_link_libraries(raytracer glfw)
