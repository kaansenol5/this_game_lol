#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Game.hpp"
#include "StartMenu.hpp"
#include "EventHandler.hpp"
class SceneManager{
public:
  SceneManager();
  ~SceneManager();
  void load_scene();
  void update(unsigned long long i);
  inline bool check_running(){
    return running;
  }
  static SDL_Renderer* renderer;
private:
  unsigned short Width;
  unsigned short Height;
  SDL_Window* window;
  char* title;
  bool running;
  Game* game_scene;
  StartMenu* start_menu_scene;
  TTF_Font* default_font;
  EventHandler* event_handler;
  int current_scene_id; //0 IS MENU, 1 IS GAME
};
