cmake_minimum_required(VERSION 3.19)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -lSDL2 -lSDL2_image -lSDL2_ttf -std=c++17")
project(NukeTown)

add_executable(
  NukeTown
  src/main.cpp
  src/Game.cpp
  src/EntityComponents/Transform.cpp
)
