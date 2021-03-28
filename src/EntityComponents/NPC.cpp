#include "NPC.hpp"
#include <iostream>
#include "../Game.hpp"
#include "../include/entt.hpp"

NPC_Component::NPC_Component(std::string type, int w, int h)
:type(type), width(w), height(h){

}

void NPC_Component::update(TransformComponent& self, TransformComponent& player, entt::registry& EntityRegistry){
  if(type=="enemy"){
    attackPlayer(self, player, EntityRegistry);
  }
  else if(type=="neutral"){
    randomMovement();
  }
}

void NPC_Component::attackPlayer(TransformComponent& self, TransformComponent& player, entt::registry& EntityRegistry){
  if(self.dst_rect.x < width + 300 && self.dst_rect.x > -300 - self.dst_rect.w  && self.dst_rect.y < height + 300 && self.dst_rect.y > -300 - self.dst_rect.h){
    if(self.dst_rect.x + self.dst_rect.w > player.dst_rect.x){
      self.move(-1,0, true, EntityRegistry);
    }
    if(self.dst_rect.x < player.dst_rect.x + player.dst_rect.w ){
      self.move(1,0, true, EntityRegistry);
    }
    if(self.dst_rect.y + self.dst_rect.h > player.dst_rect.y){
      self.move(0,-1, true, EntityRegistry);
    }
    if(self.dst_rect.y < player.dst_rect.y + player.dst_rect.h ){
      self.move(0,1, true, EntityRegistry);
    }
  }

}

void NPC_Component::randomMovement(){}
