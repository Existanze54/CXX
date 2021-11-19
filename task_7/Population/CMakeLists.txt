cmake_minimum_required(VERSION 3.4)
project(Population)
set(CMAKE_CXX_STANDRARD 20)

add_library(Population
	Person.h
	Healthy.cpp
	Infected.cpp
	Diseased.cpp
	Recovered.cpp)