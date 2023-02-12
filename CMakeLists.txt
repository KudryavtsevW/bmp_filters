cmake_minimum_required(VERSION 3.10)

project(BMP VERSION 0.0.1)

include_directories(headers)

file(GLOB SOURCES "src/*.c")

add_executable(bmp_filters ${SOURCES} "main.c")

add_subdirectory(list)

target_link_libraries(bmp_filters Library m)
