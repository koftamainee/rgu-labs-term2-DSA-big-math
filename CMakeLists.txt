cmake_minimum_required(VERSION 3.10)
project(big_math LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# file(GLOB BIGINT_SOURCES src/bigint/*.cpp) file(GLOB BIGINT_SOURCES
# src/bigint/*.cpp)
file(GLOB BIGFLOAT_SOURCES src/bigfloat/*.cpp)
file(GLOB BIGPOLY_SOURCES src/bigpoly/*.cpp)
file(GLOB BIGCOMPLEX_SOURCES src/bigcomplex/*.cpp)
file(GLOB CSTD_SOURCES src/cstd/*.cpp)

# add_library(big_math ${BIGFLOAT_SOURCES} ${BIGINT_SOURCES} ${BIGPOLY_SOURCES}
# ${BIGCOMPLEX_SOURCES} ${CSTD_SOURCES})
add_library(big_math ${BIGFLOAT_SOURCES} ${BIGPOLY_SOURCES}
                     ${BIGCOMPLEX_SOURCES} ${CSTD_SOURCES})

# Add executable target
file(GLOB EXAMPLES_SOURCES examples/*.cpp)

add_executable(rgu-labs ${EXAMPLES_SOURCES})

# Link executable with big_math library
target_link_libraries(rgu-labs big_math)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS_RELEASE
      "-O3 -march=native -flto -funroll-loops -fomit-frame-pointer -ffast-math -fno-rtti"
  )
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

  set_target_properties(big_math PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
