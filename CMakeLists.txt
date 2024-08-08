cmake_minimum_required(VERSION 3.14)

project(ascii-art LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wconversion -fsanitize=address,leak,undefined)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(src)
add_subdirectory(ascii-converter)

add_subdirectory(performance-tests)
