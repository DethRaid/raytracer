cmake_minimum_required(VERSION 3.5)
project(raytracer)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/3rdparty/glm)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/3rdparty/glfw)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_LIST_DIR}/src/3rdparty/glfw/deps)

set(SOURCE_FILES
        src/main.cpp src/ray.h src/hitables/hitable.h src/hitables/sphere.cpp src/hitables/sphere.h
        src/hitables/hitable_list.cpp src/hitables/hitable_list.h src/camera.h src/materials/material.h
        src/materials/lambertian.h src/utils.h src/materials/metal.h src/materials/dialectric.h
        src/output/output_window.cpp src/output/output_window.h
        src/3rdparty/glfw/deps/glad.c)

add_executable(raytracer ${SOURCE_FILES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY C:/Users/David/Documents/raytracer/build/bin)

add_dependencies(raytracer glfw3)
target_link_libraries(raytracer glfw)
