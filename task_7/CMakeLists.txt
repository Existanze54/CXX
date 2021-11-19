cmake_minimum_required(VERSION 3.4)
project(task_7 CXX)
set(CMAKE_CXX_STANDRARD 20)

add_executable(
    task_7
    main.cpp
)

include_directories(Population)
add_subdirectory(Population)

target_link_libraries(task_7 Population)