#include "EventHandler.hpp"
#include "EntityComponents/Transform.hpp"
#include "EntityComponents/Player.h"
#include "Map.hpp"

EventHandler::EventHandler(GameObjectManager* objects_manager, entt::registry& EntityRegistry,  int screenwidth, int screenheight, bool& game_running)
: objects_manager(objects_manager), EntityRegistry(EntityRegistry), screenwidth(screenwidth), screenheight(screenheight), game_running(game_running){
  config = JsonLoader::load("config/keybinds.json");
  keymap.left = config["left"];
  keymap.right = config["right"];
  keymap.up = config["up"];
  keymap.down = config["down"];
}

void EventHandler::HandleEvents(Map* map){
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
    case SDL_KEYDOWN:
      OnKeyDown(event.key.keysym.sym);
      break;
    case SDL_QUIT:
      game_running = false;
    default:
      break;
  }
  const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
  PlayerController(keyboard_state, map);
}

void EventHandler::PlayerController(const Uint8 *state, Map* map){
  auto players = EntityRegistry.view<Player>();
  for(auto player : players){
    TransformComponent &player_transform = EntityRegistry.get<TransformComponent>(player);
    if(state[keymap.up]){
      if(player_transform.dst_rect.y > 200){
        player_transform.move(0, -1, true, EntityRegistry);
        map->scrolled_y = false;
      }
      else{
        map->scroll(0, player_transform.movement_speed_y);

      }
    }

    if(state[keymap.down]){
      if(player_transform.dst_rect.y < screenheight -200){
        player_transform.move(0, 1, true, EntityRegistry);
        map->scrolled_y = false;
      }
      else{
        map->scroll(0, -1*player_transform.movement_speed_y);

      }
    }

    if(state[keymap.left]){
      if(player_transform.dst_rect.x > 200){
        player_transform.move(-1, 0, true, EntityRegistry);
        map->scrolled_x = false;
      }
      else{
        map->scroll(player_transform.movement_speed_x,0);

      }
    }

    if(state[keymap.right]){
      if(player_transform.dst_rect.x < screenwidth -200){
        player_transform.move(1, 0, true, EntityRegistry);
        map->scrolled_x = false;
      }
      else{
        map->scroll(player_transform.movement_speed_x*-1, 0);

      }
    }

  }



}

void EventHandler::OnKeyDown(SDL_Keycode sym){
  switch (sym) {
    case SDLK_ESCAPE:
      game_running = false;
  }
}
