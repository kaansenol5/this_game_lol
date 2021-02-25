#pragma once
#include "Entity.hpp"

class Player : public Entity{
public:
  Player(char* texturesheet, SDL_Rect dstrect, int actual_width, int actual_height, int sprite_amount, int movement_speed);
  ~Player();
  void HandleMovement(const Uint8* state);
};
