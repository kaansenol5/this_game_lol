#pragma once
#include "TransformComponent.hpp"
#include "../GameObjectManager.hpp"
#include <string>



class NPCComponent{
public:
  NPCComponent(std::string type);
  void update();
private:
  std::string type;
  void attackPlayer();
  void randomMovement();
};
