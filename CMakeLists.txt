cmake_minimum_required(VERSION 4.2)
project(console_image_editor)

set(CMAKE_CXX_STANDARD 11)

add_executable(console_image_editor)

target_sources(console_image_editor PRIVATE main.cpp)

target_include_directories(console_image_editor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)
