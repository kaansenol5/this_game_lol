#include "SceneManager.hpp"
#include <SDL2/SDL_events.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "JsonLoader.hpp"
#include "Game.hpp"


SDL_Renderer* SceneManager::renderer = nullptr;
unsigned short SceneManager::Width = 0;
unsigned short SceneManager::Height = 0;

SceneManager::SceneManager(){
  current_scene_id = 0;
  if((SDL_Init(SDL_INIT_EVERYTHING) != 0)){
    std::cout << "SDL INIT FAILED errorcode: " << SDL_GetError() << std::endl;
    exit(1);
  }
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();
  auto j = JsonLoader::load((char*)"config/game_config.json");
  Width=j["width"];
  Height=j["height"];
  std::string name = j["name"];
  window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, 0);
  if(!window){
    std::cout << "Window not created " << SDL_GetError() << std::endl;
    exit(1);
  }
  renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
  if(!renderer){
    std::cout << "Renderer not created " << SDL_GetError() << std::endl;
    exit(1);
  }
  SDL_RenderClear(renderer); //clear the screen
  SDL_RenderPresent(renderer);
  running = true;
  start_menu_scene = new UI(renderer, Width, Height, current_scene_id);
  game_scene = new Game(window, renderer, Width, Height, running);

}

SceneManager::~SceneManager(){ // this should only be called by main.cpp after the loop ends, all scenes must set running to false when their destructor is called
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  std::cout << "SceneManager.cpp goes bye-bye" << std::endl;
}

void SceneManager::update(unsigned long long i){
  if(current_scene_id == 0){
    start_menu_scene -> render();
  }
  else if(current_scene_id == 1){
    game_scene->render();
    game_scene->update(i);
  }
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
    case SDL_QUIT:
      delete game_scene;
      delete this;
  }
}
