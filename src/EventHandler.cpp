#include "EventHandler.hpp"
#include "Game.hpp"
#include "EntityComponents/Transform.hpp"
#include "EntityComponents/Player.h"

EventHandler::EventHandler(){
  config = JsonLoader::load("config/keybinds.json");
}

void EventHandler::HandleEvents(){
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
    case SDL_KEYDOWN:
      OnKeyDown(event.key.keysym.sym);
      break;
    default:
      break;
  }
  const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
  PlayerController(keyboard_state);
}

void EventHandler::PlayerController(const Uint8 *state){
  auto players = Game::EntityRegistry.view<Player>();
  for(auto player : players){
    TransformComponent &player_transform = Game::EntityRegistry.get<TransformComponent>(player);
    if(state[config["up"]]){
      player_transform.move(0, player_transform.movement_speed*-1);
    }
    if(state[config["down"]]){
      player_transform.move(0, player_transform.movement_speed);
    }
    if(state[config["left"]]){
      player_transform.move(player_transform.movement_speed*-1, 0);
    }
    if(state[config["right"]]){
      player_transform.move(player_transform.movement_speed, 0);
    }
  }


}

void EventHandler::OnKeyDown(SDL_Keycode sym){
  switch (sym) {
    case SDLK_ESCAPE:
      exit(0);
  }
}
