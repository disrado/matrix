cmake_minimum_required(VERSION 3.8)

project(matrix-project LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

add_subdirectory(modules/libmatrix)
add_subdirectory(modules/matrix)

if (ENABLE_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif ()