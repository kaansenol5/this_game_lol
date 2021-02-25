#include "Game.hpp"
#include "EventHandler.hpp"
#include <iostream>
int main(){
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;
  Uint32 frameStart;
  int frameTime;

  Game* game;
  EventHandler* eventhandler;
  game = new Game;
  eventhandler = new EventHandler;
  int i = 0;
  while (game->running){
    frameStart = SDL_GetTicks();

    game->updateFrame(i);
    i++;
    std::cout << i << "\n";
    eventhandler->HandleEvents();
    frameTime = SDL_GetTicks() - frameStart;
    if(frameDelay > frameTime){
      SDL_Delay(frameDelay - frameTime);
    }
  }
}
