cmake_minimum_required(VERSION 3.19)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -lSDL2 -lSDL2_image -lSDL2_ttf -std=c++17 -pthread -O3")
set(CMAKE_CXX_STANDARD 17)
option(USE_CLANG "build application with clang" ON)
project(NukeTown)

add_executable(
  NukeTown
  src/main.cpp
  src/Game.cpp
  src/Map.cpp
  src/EventHandler.cpp
  src/GameObjectManager.cpp
  src/EntityComponents/Transform.cpp
  src/EntityComponents/NPC.cpp
)
