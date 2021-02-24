#pragma once
#include "GameObject.hpp"

class Player : public GameObject{
public:
  Player(char* texturesheet, SDL_Rect dstrect, int actual_width, int actual_height, int sprite_amount, int movement_speed);
  ~Player();
  void HandleMovement(const Uint8* state);
  //void update();
  virtual void render();
private:
  int movement_speed;
};
