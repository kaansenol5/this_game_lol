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
      if(player_transform.dst_rect.y > 200){
        player_transform.move(0, -1, true);
        Game::map->scrolled_y = false;
      }
      else{
        Game::map->scroll(0, player_transform.movement_speed_y);

      }
    }

    if(state[config["down"]]){
      if(player_transform.dst_rect.y < Game::Height -200){
        player_transform.move(0, 1, true);
        Game::map->scrolled_y = false;
      }
      else{
        Game::map->scroll(0, -1*player_transform.movement_speed_y);

      }
    }

    if(state[config["left"]]){
      if(player_transform.dst_rect.x > 200){
        player_transform.move(-1, 0, true);
        Game::map->scrolled_x = false;
      }
      else{
        Game::map->scroll(player_transform.movement_speed_x,0);

      }
    }

    if(state[config["right"]]){
      if(player_transform.dst_rect.x < Game::Width -200){
        player_transform.move(1, 0, true);
        Game::map->scrolled_x = false;
      }
      else{
        Game::map->scroll(player_transform.movement_speed_x*-1, 0);

      }
    }

  }



}

void EventHandler::OnKeyDown(SDL_Keycode sym){
  switch (sym) {
    case SDLK_ESCAPE:
      exit(0);
  }
}
