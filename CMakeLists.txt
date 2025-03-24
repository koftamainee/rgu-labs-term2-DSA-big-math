cmake_minimum_required(VERSION 3.10)
project(big_math LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB BIGINT_SOURCES src/bigint/*.cpp)
file(GLOB BIGFLOAT_SOURCES src/bigfloat/*.cpp)
file(GLOB BIGPOLY_SOURCES src/bigpoly/*.cpp)
file(GLOB BIGCOMPLEX_SOURCES src/bigcomplex/*.cpp)


add_library(big_math ${BIGFLOAT_SOURCES} ${BIGINT_SOURCES} ${BIGPOLY_SOURCES} ${BIGCOMPLEX_SOURCES})

file(GLOB EXAMPLES_SOURCES examples/*.cpp)

add_executable(rgu-labs ${EXAMPLES_SOURCES})

target_link_libraries(rgu-labs big_math)



