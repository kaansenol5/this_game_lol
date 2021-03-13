#include "Game.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include "JsonLoader.hpp"
#include <SDL2/SDL_image.h>
#include <thread>

int Game::Width = 0;
int Game::Height = 0;
SDL_Renderer* Game::renderer = nullptr;
entt::registry Game::EntityRegistry = entt::registry();
entt::entity Game::player = entt::null;
Map* Game::map = nullptr;
GameObjectManager* Game::objects_manager = nullptr;

Game::Game(int window_position_x, int window_position_y){
  if((SDL_Init(SDL_INIT_EVERYTHING) != 0)){
    std::cout << "SDL INIT FAILED errorcode: " << SDL_GetError() << std::endl;
    exit(1);
  }
  IMG_Init(IMG_INIT_PNG);
  auto j = JsonLoader::load((char*)"config/game_config.json");

  Width=j["width"];
  Height=j["height"];
  std::string name = j["name"];
  window = SDL_CreateWindow(name.c_str(), window_position_x, window_position_y, Width, Height, 0);
  if(!window){
    std::cout << "Window not created " << SDL_GetError() << std::endl;
  }
  renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
  if(!renderer){
    std::cout << "Renderer not created " << SDL_GetError() << std::endl;
  }
  SDL_SetRenderDrawColor(renderer, 255,255,255,255); //set default rendering color to white (rgba)
  if(window&&renderer){
    running = true;
  }
  else{
    running = false;
  }
  objects_manager = new GameObjectManager;
  objects_manager->spawn(0, 300, 300);
  map = new Map;
//  map->offset_x = 6000;
  //map->offset_y = 6000;

}


void Game::render(){
  SDL_RenderClear(renderer);
  map->render();
  objects_manager->render_all();
  SDL_RenderPresent(renderer);
}

void Game::update(int i){
  objects_manager->update();
  if(i%600 == 0){
    objects_manager->enemy_spawn_random();
  }
  map->scrolled_x = false;
  map->scrolled_y = false;
}



bool Game::check_running(){
  return running;
}
