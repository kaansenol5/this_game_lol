#include "SceneManager.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include "JsonLoader.hpp"
#include "Game.hpp"

SceneManager::SceneManager(){
  if((SDL_Init(SDL_INIT_EVERYTHING) != 0)){
    std::cout << "SDL INIT FAILED errorcode: " << SDL_GetError() << std::endl;
    exit(1);
  }
  IMG_Init(IMG_INIT_PNG);
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
  running = true;
  game_scene = new Game(window, renderer, Width, Height);

}

void SceneManager::update(unsigned long long i){
  game_scene->update(i);
  game_scene->render();
}
