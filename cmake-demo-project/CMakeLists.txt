cmake_minimum_required(VERSION 3.4)

project(demoproject CXX)

set(BUILD_SHARED_LIBS 0)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")

add_subdirectory(demoprog)
add_subdirectory(demolib)

enable_testing()
add_subdirectory(tests)
