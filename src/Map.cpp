#include "Map.hpp"
#include "TextureManager.hpp"
#include <iostream>
#include <string>

Map::Map(){
  json c = JsonLoader::load("config/map_config.json");
  config = c;
  int amount_of_types = config["amount_of_types"];
  for(int i = 0; i < amount_of_types; i++){
    std::cout << amount_of_types << std::endl;
    TileType tiletype = {TextureManager::load_texture(config[std::to_string(i)]["asset"]), config[std::to_string(i)]["variations"]};
    tile_types.push_back(tiletype);
  }
  RandomGeneration();
}

bool Map::scrolled = false;

void Map::RandomGeneration(){
  unsigned long i = 0;
  //srand((int)time(0));
  while(i<config["map_size_x"]){
    i++;
  //  std::cout << "aaaa" << std::endl;
    std::vector<Tile> new_vec;
    unsigned long ii = 0;
    while(ii<config["map_size_y"]){
      ii++;
      int val1 = rand() % (int)config["amount_of_types"];
      int val2 = rand() % tile_types[val1].variations;
      Tile tile = {val1, val2};
      new_vec.push_back(tile);
    }
    game_map.push_back(new_vec);
  }


}
void Map::scroll(int x, int y){
  if(offset_x+x <= 0 && offset_x+x < config["map_size_x"]){
    offset_x += x;
  }
  if(offset_y+y <= 0 && offset_y+y < config["map_size_y"]){
    offset_y += y;
  }
  scrolled = true;
}


void Map::render(){
  for(int i = 0; i < game_map.size(); i++){
    for(int ii = 0; ii < game_map[i].size(); ii++){

        int source_x = 32 * (game_map[i][ii].asset);
      //  std::cout << "tile rendered" << std::endl;

        SDL_Rect src_rect = {source_x, 0, 32, 32};
        SDL_Rect dst_rect = {32 * i + offset_x - 32, 32 * ii + offset_y - 32, 32, 32};

        if(dst_rect.x >= -5*32  && dst_rect.x <= Game::Width + 5*32){
        //  std::cout << "yoo" << std::endl;
          if(dst_rect.y >= -5*32  && dst_rect.y <= Game::Height + 5*32){
          //  std::cout << game_map[i][ii].type << std::endl;
          SDL_RenderCopy(Game::renderer, tile_types[game_map[i][ii].type].texture, &src_rect , &dst_rect);
            }
          }
        }
    }
  }
