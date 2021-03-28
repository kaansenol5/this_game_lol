#include "Map.hpp"
#include "TextureManager.hpp"
#include "EntityComponents/Transform.hpp"
#include "EntityComponents/Player.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

Map::Map(GameObjectManager* objects_manager) : objects_manager(objects_manager){
  json c = JsonLoader::load("config/map_config.json");
  config = c;
  int amount_of_types = config["amount_of_types"];
  for(int i = 0; i < amount_of_types; i++){
    TileType tiletype = {TextureManager::load_texture(config[std::to_string(i)]["asset"]), config[std::to_string(i)]["variations"], config[std::to_string(i)]["max_repeat"]};
    tilesize = (int)config["tilesize"];
    tile_types.push_back(tiletype);
  }
  structures_to_generate = config["structures_to_generate"];
  mapsize = config["map_size"];
  mapsize = mapsize -= mapsize % std::thread::hardware_concurrency(); //makes sure that mapsize is dividable by the amount of threads present
  init_empty_map();
  random_generation();
  //generate_land_resources();
}

Map::~Map(){
  for(TileType tile: tile_types){
    SDL_DestroyTexture(tile.texture);
  }
  std::cout << "Map.cpp goes bye-bye" << std::endl;
}


void Map::init_empty_map(){
  unsigned long i = 0;
  unsigned long ii = 0;
  while(i<mapsize){
    i++;
    std::vector<Tile> new_vec;
    while(ii<mapsize){
      ii++;
      Tile tile = {0, 0};
      new_vec.push_back(tile);
    }
    ii=0;
    game_map.push_back(new_vec);

  }
}

void Map::partial_map_gen(int generate_amount){
  unsigned start_time = time(NULL);
  int amount_of_types = (int)config["amount_of_types"];
  using namespace std::chrono_literals;
  int x = 0;
  int y = 0;
  unsigned char tile_type = rand()%amount_of_types;
  int width = rand()%tile_types[tile_type].max_repeat;
  int height = rand()%tile_types[tile_type].max_repeat;

  for(int i = 0; i<generate_amount; i++){
    if(rand()%2 == 1){
      x += rand()%60 + 16;
    }
    else{
      y += rand()%60 + 16;
    }
    if(x + width > mapsize || y + height> mapsize){
      return;
    }

    //std::cout << "aaaaa" << std::endl;


    width -= width%2;
    height -= height%2;
    for(int i = x; i<width ; i++){
      unsigned char variation = rand() % tile_types[tile_type].variations;
      game_map[i][y] = {tile_type, variation};
      for(int ii = y; ii<height ; ii++){
        unsigned char variation = rand() % tile_types[tile_type].variations;
        game_map[i][ii] = {tile_type, variation};
      }
    }

    if(x>6){
      for(int i = x-5; i<x ; i++){
        unsigned char variation = rand() % tile_types[tile_type].variations;
        game_map[i][y+height/2] = {tile_type, variation};
        if(y>6){
          for(int ii = y-5; ii<y ; ii++){
            unsigned char variation = rand() % tile_types[tile_type].variations;
            game_map[i+width/2][ii] = {tile_type, variation};
          }
        }
      }
    }
  }
}



void Map::random_generation(){
  unsigned long i = 0;
  std::cout << "map generation begin" << std::endl;
  //srand((int)time(0));
  unsigned int avaliable_threads = std::thread::hardware_concurrency();
  std::cout << avaliable_threads << " threads detected" << std::endl;
  std::vector<std::thread> threads;
  int generator = structures_to_generate / avaliable_threads;
  while(i<structures_to_generate){
    unsigned long ii = 0;

    std::thread(&Map::partial_map_gen ,this, generator).detach();
    i+=generator;
    //std::cout << i/10000 << std::endl;
  }
  std::cout << "all map gen threads started" << std::endl;

}
void Map::scroll(int x, int y){
  if(offset_x+x <= 0 && offset_x+x < mapsize && x!=0){
    offset_x += x;
    scrolled_x = true;
    objects_manager->move_all(x, y);


  }
  if(offset_y+y <= 0 && offset_y+y < mapsize && y!=0){
    offset_y += y;
    scrolled_y = true;
    objects_manager->move_all(x, y);
  }

}


void Map::render(int width, int height){
  int tile_real_size = config["tile_real_size"];
  int roffset_x = -1*offset_x/32;
  int roffset_y = -1*offset_y/32;
  for(long i = roffset_x; i < roffset_x + width; i++){
    for(long ii = roffset_y; ii < roffset_y + height; ii++){
        short source_x = tilesize * (game_map[i][ii].asset); // GETS THE SOURCE RECT X FOR TILE VARIATIONS
        SDL_Rect src_rect = {source_x, 0, tile_real_size, tile_real_size};
        short x = tilesize * i + offset_x; //OFFSETS GET INCERASED AS PLAYER MOVES
        short y = tilesize * ii + offset_y;
        SDL_Rect dst_rect = {x, y, tilesize, tilesize};

        TextureManager::render(tile_types[game_map[i][ii].type].texture, &src_rect, &dst_rect);
        }
    }
  }
