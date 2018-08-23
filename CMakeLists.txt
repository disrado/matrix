cmake_minimum_required(VERSION 3.8)

project(matrix-project LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

if (ENABLE_COVERAGE)
	include(Coverage)
endif ()

add_subdirectory(modules/libmatrix)
add_subdirectory(modules/matrix)

if (ENABLE_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif ()