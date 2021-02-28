#include "Game.hpp"
#include <iostream>
#include <ctime>

int Game::Width = 0;
int Game::Height = 0;
SDL_Renderer* Game::renderer = nullptr;
bool Game::running = true;


Game::Game(){
  SDL_Init(SDL_INIT_EVERYTHING);
  Width = 1920;
  Height = 1080;
  Title = "NukeTown";
  TTF_Init();
  window = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //create renderer
  SDL_SetRenderDrawColor(renderer, 255,255,255,255); //set default rendering color to white (rgba)
  running=true;

  randomEnemySpawning();
  game_map = new Map();
}


/*
void Game::updateFrame(int i){
  SDL_RenderClear(renderer);
  game_map->render();
  player->update();
  player->render();
  for(unsigned i=0; i < Enemies.size(); i++){
    Enemies[i]->update();
    Enemies[i]->render();
  }
  player->render();
  //std::cout << player->health << std::endl;
  if(i % 600 == 0){
    randomEnemySpawning();
  }
  game_map->offset_x = player->loc_x*-1;
  game_map->offset_y = player->loc_y*-1;

  SDL_RenderPresent(renderer);
}
*/

void Game::randomEnemySpawning(){
  int x = rand() % Width;
  int y = rand() % Height;


}

Game::~Game(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  TTF_Quit();
}
