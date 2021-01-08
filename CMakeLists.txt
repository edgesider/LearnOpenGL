cmake_minimum_required(VERSION 3.17)
project(learn-gl)

set(CMAKE_CXX_STANDARD 14)
include_directories(libs/glad/include)
aux_source_directory(libs/glad/src lib)
aux_source_directory(src src)

add_executable(learn-gl ${src} ${lib})
target_link_libraries(learn-gl GL glfw dl)