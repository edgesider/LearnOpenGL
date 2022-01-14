cmake_minimum_required(VERSION 3.2)
project(learn-gl)

set(CMAKE_CXX_STANDARD 14)
include_directories(libs/glad/include)

aux_source_directory(libs/glad/src lib)
aux_source_directory(src src)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(learn-gl ${src} ${lib})
target_link_libraries(learn-gl "-framework OpenGL" glfw dl)