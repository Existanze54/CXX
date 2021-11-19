cmake_minimum_required(VERSION 3.4)
project(demotests)

find_package(Threads REQUIRED)

add_executable(demotests1 test1.cpp)
add_executable(demotests2 test2.cpp)
target_link_libraries(demotests1 Threads::Threads demolib)
target_link_libraries(demotests2 demolib)
add_test(NAME demotests1 COMMAND demotests1)
add_test(NAME demotests2 COMMAND demotests2)
