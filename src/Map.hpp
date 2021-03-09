#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <array>
#include "JsonLoader.hpp"

struct Tile{
  unsigned char type;
  unsigned char asset;
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
  bool scrolled_x = false;
  bool scrolled_y = false;
private:
  void init_empty_map();
  int offset_x = 0;
  int offset_y = 0;
  int tilesize;
  json config;
  void partial_map_gen(int startx, int starty, int avaliable_threads);
  std::vector<TileType> tile_types;
  std::vector<std::vector<Tile>> game_map; //this will be either vector or very big number
//  std::vector<std::vector<int>> source_rect_map;
  SDL_Texture* grass;
  SDL_Texture* stone;
};
