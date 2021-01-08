cmake_minimum_required(VERSION 3.17)
project(learn-gl)

set(CMAKE_CXX_STANDARD 14)
include_directories(libs/glad/include)
aux_source_directory(libs/glad/src src)

add_executable(learn-gl ${src} src/main.cpp src/util.h src/Shader.cpp src/Shader.h src/Cube.cpp src/Cube.h src/Camera.cpp src/Camera.h src/Object.cpp src/Object.h src/Scene.cpp src/Scene.h)
target_link_libraries(learn-gl GL glfw dl)