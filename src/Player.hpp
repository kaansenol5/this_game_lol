#pragma once
#include "Entity.hpp"

class Player : public Entity{
public:
  unsigned int loc_x = 0;
  unsigned int loc_y = 0;
  Player(char* texturesheet, SDL_Rect dstrect, int actual_width, int actual_height, int sprite_amount, int movement_speed, short damage);
  ~Player();
  void HandleMovement(const Uint8* state);
};
