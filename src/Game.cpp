#include "Game.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include "JsonLoader.hpp"
#include <SDL2/SDL_image.h>
#include <thread>


Map* Game::map = nullptr;

Game::Game(SDL_Window* window, SDL_Renderer* renderer, int Width, int Height, bool &running) : renderer(renderer), window(window), running(running), Width(Width), Height(Height){
//  SDL_SetRenderDrawColor(renderer, 255,255,255,255); //set default rendering color to white (rgba)

  objects_manager = new GameObjectManager(Width, Height);
  objects_manager->spawn(0, rand()%(Width-200)+200, (rand()%Height-200)+200); //SPAWN "THING" WITH TAG 0
  map = new Map(objects_manager);
  eventhandler = new EventHandler(objects_manager, objects_manager -> EntityRegistry, Width, Height, game_running);
  game_running = true;
  //map->offset_x = 6000;
  //map->offset_y = 6000;
}

Game::~Game(){
  delete objects_manager;
  delete map;
  delete eventhandler;
  std::cout << "Game.cpp goes bye-bye" << std::endl;
  running = false;
}


void Game::render(){
  SDL_RenderClear(renderer);
  map->render(Width, Height);
  objects_manager->render_all();
  SDL_RenderPresent(renderer);
}

void Game::update(unsigned long long i){
  objects_manager->update(Width, Height);
  if(i%600 == 0){
    objects_manager->enemy_spawn_random(Width, Height);
  }
  map->scrolled_x = false;
  map->scrolled_y = false;
  eventhandler ->HandleEvents(map);
  if(!game_running)
    delete this;
}



bool Game::check_running(){
  return running;
}
