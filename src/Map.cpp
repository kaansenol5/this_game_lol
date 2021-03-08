#include "Map.hpp"
#include "TextureManager.hpp"
#include "EntityComponents/Transform.hpp"
#include "EntityComponents/Player.h"
#include <iostream>
#include <string>

Map::Map(){
  json c = JsonLoader::load("config/map_config.json");
  config = c;
  int amount_of_types = config["amount_of_types"];
  for(int i = 0; i < amount_of_types; i++){
    std::cout << amount_of_types << std::endl;
    TileType tiletype = {TextureManager::load_texture(config[std::to_string(i)]["asset"]), config[std::to_string(i)]["variations"]};
    tilesize = (int)config["tilesize"];
    tile_types.push_back(tiletype);
  }
  RandomGeneration();
}



void Map::RandomGeneration(){
  unsigned long i = 0;
  int mapsizex = (int)config["map_size_x"];
  int mapsizey = (int)config["map_size_x"];
  int amount_of_types = (int)config["amount_of_types"];
  std::cout << "map generation begin" << std::endl;
  //srand((int)time(0));
  while(i<mapsizex){
    i++;
  //  std::cout << "aaaa" << std::endl;
    std::vector<Tile> new_vec;
    unsigned long ii = 0;
    while(ii<mapsizey){
      ii++;
      int val1 = rand() % amount_of_types;
      int val2 = rand() % tile_types[val1].variations;
      Tile tile = {val1, val2};
      new_vec.push_back(tile);
    }
    game_map.push_back(new_vec);
  }
  std::cout << "map generated" << std::endl;


}
void Map::scroll(int x, int y){
  if(offset_x+x <= 0 && offset_x+x < config["map_size_x"] && x!=0){
    offset_x += x;
    scrolled_x = true;

  }
  if(offset_y+y <= 0 && offset_y+y < config["map_size_y"] && y!=0){
    offset_y += y;
    scrolled_y = true;

  }

}


void Map::render(){
  int tile_real_size = config["tile_real_size"];
  int roffset_x = -1*offset_x/32;
  int roffset_y = -1*offset_y/32;
  for(long i = roffset_x; i < offset_x + Game::Width; i++){
    for(long ii = roffset_y; ii < offset_y + Game::Width; ii++){
        int source_x = tilesize * (game_map[i][ii].asset); // GETS THE SOURCE RECT X FOR TILE VARIATIONS
        SDL_Rect src_rect = {source_x, 0, tile_real_size, tile_real_size};
        int x = tilesize * i + offset_x; //OFFSETS GET INCERASED AS PLAYER MOVES
        int y = tilesize * ii + offset_y;
        SDL_Rect dst_rect = {x, y, tilesize, tilesize};

        TextureManager::render(tile_types[game_map[i][ii].type].texture, src_rect, dst_rect);
        }
    }
  }
