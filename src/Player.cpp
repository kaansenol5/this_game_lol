#include "Game.hpp"

Player::Player(char* texturesheet, SDL_Rect dstrect, int actual_width, int actual_height, int sprite_amount, int movement_speed)
: GameObject(texturesheet, dstrect, actual_width, actual_height, sprite_amount), movement_speed(movement_speed){

}

Player::~Player(){}

void Player::HandleMovement(const Uint8 *state){

  if((state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) && destination_rect.x > 0){
    move(movement_speed*-1,0);
  }
  if((state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) && destination_rect.x + actual_width < Game::Width){
    move(movement_speed,0);
  }
  if((state[SDL_SCANCODE_W] || state[SDL_SCANCODE_LEFT]) && destination_rect.y > 0){
    move(0,movement_speed*-1);
  }
  if((state[SDL_SCANCODE_S] || state[SDL_SCANCODE_RIGHT]) && destination_rect.y + actual_height < Game::Height){
    move(0,movement_speed);
  }
}


void Player::render(){
  SDL_RenderCopy(Game::renderer, texture, &source_rect, &destination_rect);
}
