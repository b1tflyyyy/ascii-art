cmake_minimum_required(VERSION 3.14)

project(ascii-converter-perf-tests LANGUAGES C CXX)

add_executable(${PROJECT_NAME} performance-tests.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ~/standard-extended-cpp-lib/header-only/include)
target_link_libraries(${PROJECT_NAME} PUBLIC ascii-converter -fsanitize=address,leak,undefined)
