#include "NPC.hpp"
#include <iostream>
#include "../Game.hpp"

NPC_Component::NPC_Component(std::string type)
:type(type){
  std::cout << "initialized an npc" << std::endl;
}

void NPC_Component::update(TransformComponent& self, TransformComponent& player){
  if(type=="enemy"){
    attackPlayer(self, player);
  }
  else if(type=="neutral"){
    randomMovement();
  }
}

void NPC_Component::attackPlayer(TransformComponent& self, TransformComponent& player){
  if(self.dst_rect.x < Game::Width + 300 && self.dst_rect.x > -300 - self.dst_rect.w  && self.dst_rect.y < Game::Height + 300 && self.dst_rect.y > -300 - self.dst_rect.h){
    if(self.dst_rect.x + self.dst_rect.w > player.dst_rect.x){
      self.move(-1,0, true);
    }
    if(self.dst_rect.x < player.dst_rect.x + player.dst_rect.w ){
      self.move(1,0, true);
    }
    if(self.dst_rect.y + self.dst_rect.h > player.dst_rect.y){
      self.move(0,-1, true);
    }
    if(self.dst_rect.y < player.dst_rect.y + player.dst_rect.h ){
      self.move(0,1, true);
    }
  }

}

void NPC_Component::randomMovement(){}
