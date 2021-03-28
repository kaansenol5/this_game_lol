#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>




class StartMenu{
public:
  StartMenu(SDL_Window* window, SDL_Renderer* renderer, int& current_scene_id, bool& running);
  ~StartMenu();
  void updateFrame();
private:
  void add_text(char* font_dir, char* text, int ptsize, SDL_Rect location, SDL_Color color);
  bool& running;
  int& current_scene_id;
  SDL_Window* window;
  SDL_Renderer* renderer;

};
