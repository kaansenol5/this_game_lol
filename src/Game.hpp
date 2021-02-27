#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "TextureManager.hpp"
#include "Player.hpp"
#include <vector>
#include "Enemy.hpp"
#include "Map.hpp"

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
  static Player* player;
private:
  void randomEnemySpawning();
  Map* game_map;
  SDL_Window* window;
  std::vector<Enemy*> Enemies; //TODO: replace int with the name of enemy class
};
