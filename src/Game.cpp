#include "Game.hpp"
#include <iostream>
#include <ctime>

int Game::Width = 0;
int Game::Height = 0;
SDL_Renderer* Game::renderer = nullptr;
bool Game::running = true;
Player* Game::player = nullptr;

Game::Game(){
  SDL_Init(SDL_INIT_EVERYTHING);
  Width = 800;
  Height = 840;
  Title = "NukeTown";
  TTF_Init();
  window = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //create renderer
  SDL_SetRenderDrawColor(renderer, 255,255,255,255); //set default rendering color to white (rgba)
  running=true;
  player = new Player("assets/sprites/wizard.png", {0,0,128,128}, 32, 32,4,6, 1);
  randomEnemySpawning();
  game_map = new Map();
}

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
//  game_map->offset_x = player->destination_rect.x;
//  game_map->offset_y = player->destination_rect.y;

  SDL_RenderPresent(renderer);
}


void Game::randomEnemySpawning(){
  int x = rand() % Width;
  int y = rand() % Height;
  Enemies.push_back(new Enemy("assets/sprites/wizard.png",{x,y,128,128},32, 32, 4, 2, 1));

}

Game::~Game(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  TTF_Quit();
}
