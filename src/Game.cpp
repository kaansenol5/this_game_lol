#include "Game.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include "JsonLoader.hpp"
#include <SDL2/SDL_image.h>
#include <thread>

unsigned short Game::Width = 0;
unsigned short Game::Height = 0;
entt::registry Game::EntityRegistry = entt::registry();
entt::entity Game::player = entt::null;
Map* Game::map = nullptr;
GameObjectManager* Game::objects_manager = nullptr;

Game::Game(SDL_Window* window, SDL_Renderer* renderer, int Width, int Height) : renderer(renderer), window(window){
  Game::Width = Width;
  Game::Height = Height;
//  SDL_SetRenderDrawColor(renderer, 255,255,255,255); //set default rendering color to white (rgba)

  objects_manager = new GameObjectManager;
  objects_manager->spawn(0, rand()%(Width-200)+200, (rand()%Height-200)+200); //SPAWN "THING" WITH TAG 0
  map = new Map;
  //map->offset_x = 6000;
  //map->offset_y = 6000;
}


void Game::render(){
  SDL_RenderClear(renderer);
  map->render();
  objects_manager->render_all();
  SDL_RenderPresent(renderer);
}

void Game::update(unsigned long long i){
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
