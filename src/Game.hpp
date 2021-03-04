#pragma once
#include "include/entt.hpp"
#include <SDL2/SDL.h>
#include "Map.hpp"
//entt
//use json


class Game{
public:
  Game(int window_position_x, int window_position_y);
  ~Game();
  static int Width;
  static int Height;
  static SDL_Renderer* renderer;
  static entt::registry EntityRegistry;
  static entt::entity player;
  void updateFrame(int i);
  bool check_running();
private:
  char* title;
  bool running;
  SDL_Window* window;
  Map* map;
  void RandomEnemySpawning();
};
