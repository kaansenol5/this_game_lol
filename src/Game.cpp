#include "Game.hpp"
#include <iostream>
#include <ctime>
#include "EntityComponents/Transform.h"


int Game::Width = 0;
int Game::Height = 0;
SDL_Renderer* Game::renderer = nullptr;
bool Game::running = true;
entt::entity Game::player = entt::null;

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
  player = EntityRegistry.create();
  EntityRegistry.emplace<TransformComponent>(player, 0,0,0,0,32,32,0,0,128,128,TextureManager::load_texture("assets/sprites/wizard.png"));
  randomEnemySpawning();
  game_map = new Map();
}



void Game::updateFrame(int i){
  SDL_RenderClear(renderer);
  game_map->render();
  auto characters = EntityRegistry.view<TransformComponent>();
  for(auto entity : characters){
    TransformComponent &Transform = characters.get<TransformComponent>(entity);
    render(renderer, Transform);
  }


  //std::cout << player->health << std::endl;
  if(i % 600 == 0){
    //randomEnemySpawning();
  }

  SDL_RenderPresent(renderer);
}


void Game::randomEnemySpawning(){
  int x = rand() % Width;
  int y = rand() % Height;
  auto enemy = EntityRegistry.create();
  EntityRegistry.emplace<TransformComponent>(enemy,  x,y,0,0,32,32,x,y,128,128,TextureManager::load_texture("assets/sprites/wizard.png"));


}

Game::~Game(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  TTF_Quit();
}
