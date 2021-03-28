#pragma once
#include "include/entt.hpp"
#include <SDL2/SDL.h>
#include "Map.hpp"
#include "GameObjectManager.hpp"
#include "EventHandler.hpp"
//entt
//use json


class Game{
public:
  Game(SDL_Window* window, SDL_Renderer* renderer, int Width, int Height, bool &running);
  ~Game();
  void render();
  void update(unsigned long long i);
  bool check_running();
  Map* map;
  GameObjectManager* objects_manager;
private:
  EventHandler* eventhandler;
  int Width;
  int Height;
  SDL_Renderer* renderer;
  char* title;
  bool &running;
  bool game_running;
  SDL_Window* window;
};
