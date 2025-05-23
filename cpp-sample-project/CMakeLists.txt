cmake_minimum_required(VERSION 3.2)

project(democpp CXX)
find_package(Eigen3 3.3 REQUIRED)

add_executable(
	democpp
	main.cpp
	anothefile.cpp
	anothefile.h
	examples_arrays.cpp
	examples_branches.cpp
	examples_enums.cpp
	examples_functions.cpp
	examples_loops.cpp
	examples_namespaces.cpp
	examples_pointers.cpp
	examples_preprocessor.cpp
	examples_simple_datatypes.cpp
	examples_struct.cpp
	examples_literals.cpp
	examples_exceptions.cpp
	examples_oop.cpp
	examples_templates.cpp
	examples_functional.cpp
	examples_threads.cpp
	examples_containers.cpp
)

target_compile_features(democpp PUBLIC cxx_std_20)

if (UNIX)
	target_compile_options(democpp PUBLIC
		-pedantic-errors
		-Wno-unused-value
		-ftemplate-depth=2048
		-fconstexpr-depth=100000
	)
	target_link_libraries(democpp pthread)
elseif(WIN32)
  include_directories($ENV{EIGEN3_INCLUDE_DIR})
	target_compile_options(democpp PUBLIC /constexpr:steps5000000)
	target_compile_definitions(democpp PUBLIC _USE_MATH_DEFINES _CRT_SECURE_NO_WARNINGS)
endif()

target_compile_definitions(democpp PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")
target_link_libraries(democpp Eigen3::Eigen)
