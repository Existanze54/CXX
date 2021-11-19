cmake_minimum_required(VERSION 3.4)
project(task_6 CXX)
set(CMAKE_CXX_STANDRARD 14)

add_executable(
    task_6
    main.cpp
)

include_directories(List)
add_subdirectory(List)

target_link_libraries(task_6 List)

enable_testing()
add_subdirectory(tests)

