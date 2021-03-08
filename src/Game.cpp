#include "Game.hpp"
#include <SDL2/SDL.h>
#include "EntityComponents/Transform.hpp"
#include "EntityComponents/Player.h"
#include <iostream>
#include "JsonLoader.hpp"
#include <SDL2/SDL_image.h>
#include "EntityComponents/NPC.hpp"

int Game::Width = 0;
int Game::Height = 0;
SDL_Renderer* Game::renderer = nullptr;
entt::registry Game::EntityRegistry = entt::registry();
entt::entity Game::player = entt::null;
Map* Game::map = nullptr;

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
  player = EntityRegistry.create();
  EntityRegistry.emplace<TransformComponent>(player, 500,100,32,32,"assets/sprites/wizard.png", 3,3, 32,32, true, 3,1, true, false);
  EntityRegistry.emplace<Player>(player, true);
  entt::entity enemy = EntityRegistry.create();
  EntityRegistry.emplace<TransformComponent>(enemy, 100,500,32,32,"assets/sprites/wizard.png", 2,2, 32,32, true, 3,1, true, false);
  EntityRegistry.emplace<NPC_Component>(enemy, NPC_ENEMY);
  map = new Map;
}


void Game::updateFrame(int i){
  SDL_RenderClear(renderer);
  map->render();


  EntityRegistry.view<TransformComponent>().each([](auto entity, auto &transform_comp){
    transform_comp.render();
  });

  EntityRegistry.group<NPC_Component, TransformComponent>().each([](auto entity, auto &npc_comp, auto &transform_comp){
    npc_comp.update(transform_comp, EntityRegistry.get<TransformComponent>(player));
  });

  map->scrolled_x = false;
  map->scrolled_y = false;
  SDL_RenderPresent(renderer);
}

bool Game::check_running(){
  return running;
}
