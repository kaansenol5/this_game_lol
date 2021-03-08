#pragma once
#include "Transform.hpp"


#define NPC_ENEMY 0
#define NPC_NEUTRAL 1

class NPC_Component{
public:
  NPC_Component(std::string type);
  void update(TransformComponent& self, TransformComponent& player);
private:
  void attackPlayer(TransformComponent& self, TransformComponent& player);
  void randomMovement();
  std::string type;
};
