cmake_minimum_required(VERSION 3.14)

set(LIBRARY_NAME ascii-converter)

set(SOURCES ascii-converter.cpp)
set(HEADRES ascii-converter.hpp)

add_library(${LIBRARY_NAME} STATIC ${SOURCES} ${HEADRES})

target_link_libraries(${LIBRARY_NAME} PUBLIC ${OpenCV_LIBS})
target_include_directories(${LIBRARY_NAME} PUBLIC ./)
