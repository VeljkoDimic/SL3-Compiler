cmake_minimum_required (VERSION 2.6)
project (SL3)

SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER clang++)

set (CMAKE_CXX_FLAGS "-std=c++14")

file(COPY SL3/SL3.lr1 DESTINATION .)

file(GLOB SOURCES "src/*.cpp" "src/*.h")

add_executable(sl3 ${SOURCES})
