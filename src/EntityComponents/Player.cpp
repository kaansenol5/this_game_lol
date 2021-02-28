#include "Player.h"
#include <SDL2/SDL.h>

void KeyHandle(const Uint8 *state, TransformComponent &transform){
  if(state[SDL_SCANCODE_W]){
    transform.destination_rect.y -= transform.movement_speed;
  }
  if(state[SDL_SCANCODE_S]){
    transform.destination_rect.y += transform.movement_speed;
  }
  if(state[SDL_SCANCODE_A]){
    transform.destination_rect.x -= transform.movement_speed;
  }
  if(state[SDL_SCANCODE_D]){
    transform.destination_rect.x += transform.movement_speed;
  }
}
