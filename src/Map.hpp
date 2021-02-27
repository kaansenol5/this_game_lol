#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <array>


struct Tile{
  int type;
  int asset;
//  bool display = false;
};


class Map{
public:
  Map();
  ~Map();
  void RandomGeneration();
  void render();
  int offset_x = 0;
  int offset_y = 0;
private:
  std::vector<std::vector<Tile>> game_map; //this will be either vector or very big number
//  std::vector<std::vector<int>> source_rect_map;
  SDL_Texture* grass;
  SDL_Texture* stone;
};
