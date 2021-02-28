#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "TextureManager.hpp"
#include <vector>
#include "Map.hpp"
#include "include/entt.hpp"

class Game{
public:
  Game();
  ~Game();

  void updateFrame(int i);
  static int Width;
  static int Height;
  std::string Title;
  static SDL_Renderer* renderer;
  static bool running;
  static entt::entity player;
private:
  void randomEnemySpawning();
  Map* game_map;
  entt::registry EntityRegistry;
  SDL_Window* window;
};
