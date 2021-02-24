cmake_minimum_required(VERSION 3.19)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -lSDL2 -lSDL2_image -lSDL2_ttf")
project(NukeTown)

add_executable(
  NukeTown
  src/main.cpp
  src/Entity.cpp
  src/Game.cpp
  src/GameObject.cpp
  src/TextureManager.cpp
  src/Player.cpp
  src/EventHandler.cpp
)
