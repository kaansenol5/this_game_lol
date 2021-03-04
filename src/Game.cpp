#include "Game.hpp"
#include <SDL2/SDL.h>
#include "EntityComponents/Transform.hpp"
#include <iostream>
#include "JsonLoader.hpp"

int Game::Width = 0;
int Game::Height = 0;
SDL_Renderer* Game::renderer = nullptr;
entt::registry Game::EntityRegistry = entt::registry();
Game::Game(int window_position_x, int window_position_y){
  if((SDL_Init(SDL_INIT_EVERYTHING) != 0)){
    std::cout << "SDL INIT FAILED " << SDL_GetError() << std::endl;
    exit(1);
  }
  auto j = JsonLoader::load("config/game_config.json");

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
  entt::entity player = EntityRegistry.create();
  EntityRegistry.emplace<TransformComponent>(player, 100,100,128,128,"assets/sprites/wizard.png", 3, 32,32, true, 3, 1, true, false);
  map = new Map;
}


void Game::updateFrame(int i){
  SDL_RenderClear(renderer);
  auto renderable = EntityRegistry.view<TransformComponent>();
  map->render();
  for(auto entity : renderable){
    TransformComponent &Transform = renderable.get<TransformComponent>(entity);
    Transform.render();
  }

  SDL_RenderPresent(renderer);
}

bool Game::check_running(){
  return running;
}
