cmake_minimum_required(VERSION 3.4)
project(demoprog CXX)
add_executable(demoprog main.cpp)
target_compile_features(demoprog PUBLIC cxx_std_11)
target_link_libraries(demoprog demolib)
