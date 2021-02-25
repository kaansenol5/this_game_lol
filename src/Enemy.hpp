#include "Entity.hpp"

class Enemy : public Entity{
public:
  Enemy(char* texturesheet, SDL_Rect dstrect, int actual_width, int actual_height, int sprite_amount, int movement_speed, int damage);
  virtual ~Enemy();
  virtual void update();
private:
  void AttackPlayer();
  void HitPlayer();

};
