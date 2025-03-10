#pragma once
#include "include/entt.hpp"
#include <SDL2/SDL.h>
#include "Map.hpp"
#include "GameObjectManager.hpp"
//entt
//use json


class Game{
public:
  Game(SDL_Window* window, SDL_Renderer* renderer, int Width, int Height);
  ~Game();
  static unsigned short Width;
  static unsigned short Height;
  static SDL_Renderer* renderer;
  static entt::registry EntityRegistry;
  static entt::entity player;
  void render();
  void update(unsigned long long i);
  bool check_running();
  static Map* map;
  static GameObjectManager* objects_manager;
private:
  char* title;
  bool running;
  SDL_Window* window;
};
