cmake_minimum_required(VERSION 3.4)
project(demolib CXX)

find_package(Eigen3 3.3 REQUIRED)
find_package(Threads REQUIRED)

add_library(demolib main.cpp inc/demolib.h)
target_compile_features(demolib PUBLIC cxx_std_20)

target_link_libraries(demolib Eigen3::Eigen	${CMAKE_THREAD_LIBS_INIT})
target_include_directories(demolib PUBLIC ${PROJECT_SOURCE_DIR}/inc)
