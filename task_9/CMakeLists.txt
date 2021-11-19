cmake_minimum_required(VERSION 3.4)
project(task_9 CXX)
set(CMAKE_CXX_STANDRARD 21)

add_executable(
    task_9
    main.cpp
    TupleN.h
)
target_compile_features(task_9 PUBLIC cxx_std_20)

