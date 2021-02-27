#include "Game.hpp"

Player::Player(char* texturesheet, SDL_Rect dstrect, int actual_width, int actual_height, int sprite_amount, int movement_speed, short damage)
: Entity(texturesheet, dstrect, actual_width, actual_height, sprite_amount, movement_speed, damage){

}

Player::~Player(){}

void Player::HandleMovement(const Uint8 *state){

  if((state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])){
    if(destination_rect.x > 200){
      move(movement_speed*-1,0);
    }
    else{
      if(loc_x > 0){
        loc_x-=movement_speed;
      }
    }
  }
  if((state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])){
    if(destination_rect.x < Game::Width-200){
      move(movement_speed,0);
    }
    else{
      loc_x+=movement_speed;
    }
  }
  if((state[SDL_SCANCODE_W] || state[SDL_SCANCODE_LEFT])){
    if(destination_rect.y > 200){
      move(0, movement_speed * -1);
    }
    else{
      if(loc_y > 0){
        loc_y-=movement_speed;
      }
    }
  }
  if((state[SDL_SCANCODE_S] || state[SDL_SCANCODE_RIGHT])){
    if(destination_rect.y < Game::Height-200){
      move(0, movement_speed);
    }
    else{
      loc_y+=movement_speed;
    }
  }
}
