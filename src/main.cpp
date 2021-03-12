#include "Game.hpp"
#include "EventHandler.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <thread>

int main(){
  srand((unsigned) time(NULL));
  Game* game;
  EventHandler* eventhandler;
  eventhandler = new EventHandler;
  game = new Game(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;
  Uint32 frameStart;
  int frameTime;
  int i = 0;
  while (game->check_running()){
    frameStart = SDL_GetTicks();
    game->update(i);
    game->render();
    i++;
    eventhandler->HandleEvents();
    frameTime = SDL_GetTicks() - frameStart;
    if(frameDelay > frameTime){
      SDL_Delay(frameDelay - frameTime);
    }
  }
}
