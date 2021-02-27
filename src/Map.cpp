#include "Map.hpp"
#include "Game.hpp"
#include <iostream>

Map::Map(){
  RandomGeneration();
  grass = TextureManager::load_texture("assets/tiles/dirt.png");
  stone = TextureManager::load_texture("assets/tiles/stone.png");
}

void Map::RandomGeneration(){
  int i = 0;
  //srand((int)time(0));
  while(i<1000){
    i++;
  //  std::cout << "aaaa" << std::endl;
    std::vector<Tile> new_vec;
    int ii = 0;
    while(ii<1000){
      ii++;
      int val1 = rand() % 2;
      int val2 = rand() % 2;
      Tile tile = {val1, val2};
      new_vec.push_back(tile);
    }
    game_map.push_back(new_vec);
  }


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
            switch (game_map[i][ii].type) {
              case 0:
                SDL_RenderCopy(Game::renderer, grass, &src_rect , &dst_rect);
                break;
              //  std::cout << i << " " << ii << std::endl;
              case 1:
                SDL_RenderCopy(Game::renderer, stone, &src_rect , &dst_rect);
                break;

              }
            }
          }
        }
    }
  }
