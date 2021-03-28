#pragma once
#include "Transform.hpp"


#define NPC_ENEMY 0
#define NPC_NEUTRAL 1

class NPC_Component{
public:
  NPC_Component(std::string type, int w, int h);
  void update(TransformComponent& self, TransformComponent& player, entt::registry& EntityRegistry);
private:
  int width;
  int height;
  void attackPlayer(TransformComponent& self, TransformComponent& player, entt::registry& EntityRegistry);
  void randomMovement();
  std::string type;
};
