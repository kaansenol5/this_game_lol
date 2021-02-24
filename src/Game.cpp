#include "Game.hpp"


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
  player = new Player("assets/sprites/wizard.png", {0,0,128,128}, 32, 32,4,6);

}

void Game::update(){
  player->update();
}


void Game::render(){
  SDL_RenderClear(renderer);
  player->render();
  SDL_RenderPresent(renderer);
}

Game::~Game(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  TTF_Quit();
}
