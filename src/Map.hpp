#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <array>
#include "JsonLoader.hpp"

struct Tile{
  int type;
  int asset;
//  bool display = false;
};

struct TileType{
  SDL_Texture* texture;
  int variations;
};


class Map{
public:
  Map();
  ~Map();
  void RandomGeneration();
  void render();
  void scroll(int x, int y);
  static bool scrolled;
private:
  int offset_x = 0;
  int offset_y = 0;
  json config;
  std::vector<TileType> tile_types;
  std::vector<std::vector<Tile>> game_map; //this will be either vector or very big number
//  std::vector<std::vector<int>> source_rect_map;
  SDL_Texture* grass;
  SDL_Texture* stone;
};
