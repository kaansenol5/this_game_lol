#include "Game.hpp"
#include <SDL2/SDL.h>
#include "EntityComponents/Transform.hpp"
#include "Renderer.hpp"

int Game::Width = 0;
int Game::Height = 0;
SDL_Renderer* Game::renderer = nullptr;

Game::Game(char* title, int w, int h, int window_position_x, int window_position_y){
  if((SDL_Init(SDL_INIT_EVERYTHING) != 0)){
    exit(1);
  }
  Width=w;
  Height=h;
  window = SDL_CreateWindow(title, window_position_x, window_position_y, Width, Height, 0);
  renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(renderer, 255,255,255,255); //set default rendering color to white (rgba)
  entt::entity player = EntityRegistry.create();
  EntityRegistry.emplace<TransformComponent>(player, )

}
