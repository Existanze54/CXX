cmake_minimum_required(VERSION 3.4)
project(task_5 CXX)
set(CMAKE_CXX_STANDRARD 14)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang") # using Clang  
add_compile_options(-pedantic) 
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") # using GCC
add_compile_options(-pedantic)
endif()


add_executable(
    task_5
    main.cpp
    Vector3D.cpp
    Vector3D.h
)