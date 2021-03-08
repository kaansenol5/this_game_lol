#include "Transform.hpp"


#define NPC_ENEMY 0
#define NPC_NEUTRAL 1

class NPC_Component{
public:
  NPC_Component(unsigned short type);
  void update(TransformComponent& self, TransformComponent& player);
private:
  void attackPlayer(TransformComponent& self, TransformComponent& player);
  void randomMovement();
  unsigned short type;
};
