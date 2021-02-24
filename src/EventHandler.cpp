#include "EventHandler.hpp"

void EventHandler::HandleEvents(){
  SDL_PollEvent(&event);
  HandleBaseEvents();
  HandlePlayerEvents();
}

void EventHandler::HandlePlayerEvents(){
  const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
  Game::player->HandleMovement(keyboard_state);
}

void EventHandler::HandleBaseEvents(){
  switch(event.type){
    case SDL_QUIT:
      Game::running = false;
      break;
    default:
      break;
  }
}
