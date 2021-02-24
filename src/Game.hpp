#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "TextureManager.hpp"
#include "Player.hpp"
class Game{
public:
  Game();
  ~Game();
  void render();
  void update();
  static int Width;
  static int Height;
  std::string Title;
  static SDL_Renderer* renderer;
  static bool running;
  static Player* player;
private:
  SDL_Window* window;

};
