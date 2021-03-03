#pragma once
#include "include/entt.hpp"
#include <SDL2/SDL.h>

//entt
//use json


class Game{
public:
  Game(char* title, int w, int h, int window_position_x, int window_position_y);
  ~Game();
  static int Width;
  static int Height;
  static SDL_Renderer* renderer;
  static entt::registry EntityRegistry;
  void update(int i);
  void render();
private:
  char* title;
  SDL_Window* window;
  void RandomEnemySpawning();
};
