cmake_minimum_required(VERSION 3.10)

project(MyProject)

add_executable(MyProject src/script.cpp)

target_include_directories(MyProject
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)
