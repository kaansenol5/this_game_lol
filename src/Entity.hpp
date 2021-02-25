#pragma once
#include "GameObject.hpp"

class Entity : public GameObject{
public:
  Entity(char* texturesheet, SDL_Rect dstrect, int actual_width, int actual_height, int sprite_amount, int movement_speed, int damage);
  virtual ~Entity();
  //virtual void update();
  unsigned short health;
  unsigned short damage;
  unsigned short movement_speed;
  bool attacking = false;
};
