#pragma once
#include <SDL2/SDL.h>
#include "Game.hpp"

class SceneManager{
public:
  SceneManager();
  ~SceneManager();
  void load_scene();
  void update(unsigned long long i);
  inline bool check_running(){
    return running;
  }
private:
  unsigned short Width;
  unsigned short Height;
  SDL_Window* window;
  SDL_Renderer* renderer;
  char* title;
  bool running;
  Game* game_scene;
  int current_scene_id; //0 IS MENU, 1 IS GAME
};
