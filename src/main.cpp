#include <SDL2/SDL.h>
#include <iostream>
#include <thread>
#include "SceneManager.hpp"

int main(){
  srand((unsigned) time(NULL));
  SceneManager* scenemanager;
  scenemanager = new SceneManager;
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;
  Uint32 frameStart;
  int frameTime;
  unsigned long long i = 0;
  while (scenemanager->check_running()){
    frameStart = SDL_GetTicks();
    scenemanager->update(i);
    i++;

    frameTime = SDL_GetTicks() - frameStart;
    if(frameDelay > frameTime){
      SDL_Delay(frameDelay - frameTime);
    }
  }
  delete scenemanager;
  std::cout << "main.cpp goes bye-bye" << std::endl;
  return 0;
}
