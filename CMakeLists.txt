cmake_minimum_required(VERSION 3.19)
INCLUDE(FindPkgConfig)
project(NukeTown)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -lSDL2 -lSDL2_image -lSDL2_ttf -std=c++17 -pthread -O0")
set(CMAKE_CXX_STANDARD 17)
option(USE_CLANG "build application with clang" ON)


add_executable(
  NukeTown
  src/main.cpp
  src/Game.cpp
  src/Map.cpp
  src/EventHandler.cpp
  src/GameObjectManager.cpp
  src/SceneManager.cpp
  src/EntityComponents/Transform.cpp
  src/EntityComponents/NPC.cpp
  src/UI/Button.cpp
  src/UI/Text.cpp
  src/UI/Menu.cpp
  src/UI/UI.cpp
)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

