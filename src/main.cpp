#include "Game.hpp"
#include <SDL2/SDL.h>
#include <iostream>

int main(){
  srand((unsigned) time(NULL));
  Game* game;
  game = new Game("GameMoment", 400, 400, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;
  Uint32 frameStart;
  int frameTime;
  int i = 0;
  while (game->check_running()){
    //frameStart = SDL_GetTicks();

    game->updateFrame(i);
    i++;
    exit(0);
  //  std::cout << i << "\n";
    frameTime = SDL_GetTicks() - frameStart;
    if(frameDelay > frameTime){
      SDL_Delay(frameDelay - frameTime);
    }
    std::cout << sizeof(game) << std::endl;
  }
}
