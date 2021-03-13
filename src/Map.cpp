#include "Map.hpp"
#include "TextureManager.hpp"
#include "EntityComponents/Transform.hpp"
#include "EntityComponents/Player.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

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
  auto start_time = time(NULL);
  init_empty_map();
  std::cout << "mapinit takes " << time(NULL) - start_time << " secs" << std::endl;
  random_generation();
  //generate_land_resources();
  std::thread(&Map::generate_land_resources, this).detach();

}


void Map::init_empty_map(){
  unsigned long mapsizex = (int)config["map_size"];
  unsigned long i = 0;
  unsigned long ii = 0;
  while(i<mapsizex){
    i++;
    std::vector<Tile> new_vec;
    while(ii<mapsizex){
      ii++;
      Tile tile = {0, 0};
      new_vec.push_back(tile);
    }
    ii=0;
    game_map.push_back(new_vec);

  }
}

void Map::partial_map_gen(int startx, int starty, int avaliable_threads){
  std::cout << "partial map generation thread started" << std::endl;
  unsigned start_time = time(NULL);
  int i = startx;
  int ii = starty;
  unsigned long mapsizex = (int)config["map_size"];
  int endx = i + mapsizex/avaliable_threads;
  int endy = ii + mapsizex/avaliable_threads;
  int amount_of_types = (int)config["amount_of_types"];
  using namespace std::chrono_literals;
  while(i<endx-1){
  //  std::cout << "aaaa" << std::endl;
    int ii = starty;
    while(ii<endy-1){
      unsigned char val1 = rand() % amount_of_types;
      unsigned char val2 = rand() % tile_types[val1].variations;
      Tile tile = {val1, val2};
      game_map[i][ii] = tile;
      ii++;
    //  std::this_thread::sleep_for(1ns);

    }
    i++;
  }
  std::cout << "partial map generation thread took " << time(NULL) - start_time << "seconds" << std::endl;
  std::cout << "generated map between x: " << startx << " - " << endx << " y: " << starty << " - " << endy << std::endl;
  return;
}

void Map::generate_land_resources(){
  std::cout << "bbb" << std::endl;
  unsigned long mapsize = (int)config["map_size"];
  unsigned short resource_amount = config["resource_amount"];
  std::cout << resource_amount << std::endl;
  for(unsigned short i = 0; i < resource_amount; i++){
    Game::objects_manager->landresource_spawn_random(mapsize, tilesize);
  }
  std::cout << "land resources generated" << std::endl;
}

void Map::random_generation(){
  unsigned long i = 0;
  unsigned long mapsizex = (int)config["map_size"];
  std::cout << "map generation begin" << std::endl;
  //srand((int)time(0));
  unsigned int avaliable_threads = std::thread::hardware_concurrency();
  std::cout << avaliable_threads << std::endl;
  std::vector<std::thread> threads;
  while(i<mapsizex){
    unsigned long ii = 0;

    std::thread(&Map::partial_map_gen ,this,i,i,avaliable_threads).detach();
    while(ii<mapsizex){
      //std::thread(&Map::partial_map_gen ,this,i,ii).detach();
    //  std::cout << "thread call" <<std::endl;
      ii+=mapsizex/avaliable_threads;
    }
    i+=mapsizex/avaliable_threads;
    //std::cout << i/10000 << std::endl;
  }
  std::cout << "all map gen threads started" << std::endl;

}
void Map::scroll(int x, int y){
  if(offset_x+x <= 0 && offset_x+x < config["map_size"] && x!=0){
    offset_x += x;
    scrolled_x = true;
    Game::objects_manager->move_all(x, y);


  }
  if(offset_y+y <= 0 && offset_y+y < config["map_size_y"] && y!=0){
    offset_y += y;
    scrolled_y = true;
    Game::objects_manager->move_all(x, y);
  }

}


void Map::render(){
  int tile_real_size = config["tile_real_size"];
  int roffset_x = -1*offset_x/32;
  int roffset_y = -1*offset_y/32;
  for(long i = roffset_x; i < roffset_x + Game::Width; i++){
    for(long ii = roffset_y; ii < roffset_y + Game::Height; ii++){
        short source_x = tilesize * (game_map[i][ii].asset); // GETS THE SOURCE RECT X FOR TILE VARIATIONS
        SDL_Rect src_rect = {source_x, 0, tile_real_size, tile_real_size};
        short x = tilesize * i + offset_x; //OFFSETS GET INCERASED AS PLAYER MOVES
        short y = tilesize * ii + offset_y;
        SDL_Rect dst_rect = {x, y, tilesize, tilesize};

        TextureManager::render(tile_types[game_map[i][ii].type].texture, src_rect, dst_rect);
        }
    }
  }
