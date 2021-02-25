#include "GameObject.hpp"

class Enemy : public GameObject{
public:
  Enemy(char* texturesheet, SDL_Rect dstrect, int actual_width, int actual_height, int sprite_amount, int movement_speed, int damage);
  virtual ~Enemy();
  void AttackPlayer();
  void HitPlayer();
  virtual void update();
  int health;
private:
  int movement_speed;
  int damage;
  bool attacking = false;
};
