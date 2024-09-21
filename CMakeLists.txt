cmake_minimum_required(VERSION 3.14)

project(ascii-art LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_options(/Wall)
else()
	add_compile_options(-Wall -Wextra -Wconversion)
endif()

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(src)
add_subdirectory(ascii-converter)