#pragma once
#include "TransformComponent.hpp"
#include "../GameObjectManager.hpp"

enum Type{
  ENEMY, NEUTRAL
};

class NPC_Component{
public:
  NPC_Component(Type type);
  void update();
private:
  Type type;
  int width;
  int height;
  void attackPlayer();
  void randomMovement();
};
