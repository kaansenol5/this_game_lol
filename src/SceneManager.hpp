#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Game.hpp"
#include "EventHandler.hpp"
#include "UI/UI.hpp"


class SceneManager{
public:
  SceneManager();
  ~SceneManager();
  void load_scene();
  void update(unsigned long long i);
  inline bool check_running(){
    return running;
  }
  static void quit_game();
  static SDL_Renderer* renderer;
  static unsigned short Width;
  static unsigned short Height;
private:
  SDL_Window* window;
  char* title;
  bool running;
  Game* game_scene;
  UI* start_menu_scene;
  TTF_Font* default_font;
  int current_scene_id; //0 IS MENU, 1 IS GAME
};
