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
  unsigned char variations;
  unsigned char max_repeat;
};


class Map{
public:
  Map();
  ~Map();
  void render();
  void scroll(int x, int y);
  bool scrolled_x = false;
  bool scrolled_y = false;
  int offset_x = 0;
  int offset_y = 0;
private:
  void random_generation();
  void init_empty_map();
  int tilesize;
  int mapsize;
  int structures_to_generate;
  json config;
  void partial_map_gen(int generate_amount);
  std::vector<TileType> tile_types;
  std::vector<std::vector<Tile>> game_map; //this will be either vector or very big number
//  std::vector<std::vector<int>> source_rect_map;
  SDL_Texture* grass;
  SDL_Texture* stone;
};
