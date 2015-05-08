cmake_minimum_required(VERSION 2.8)
project(bally)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O3")

include_directories(
  ${CMAKE_SOURCE_DIR}/src/
  vendor/lodepng)

set(src
  vendor/lodepng/lodepng.cpp
  src/object/mesh.cpp
  src/object/plane.cpp
  src/object/polygon.cpp
  src/object/sphere.cpp
  src/texture/texture.cpp
  src/type/color.cpp
  src/type/intersection.cpp
  src/type/material.cpp
  src/type/ray.cpp
  src/type/vector.cpp
  src/light.cpp
  src/scene.cpp
  src/utils.cpp
  src/main.cpp)

add_executable(bally ${src})
target_link_libraries(bally)
