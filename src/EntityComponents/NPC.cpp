#include "NPC.hpp"
#include <iostream>
#include "../Game.hpp"

NPC_Component::NPC_Component(unsigned short type)
:type(type){
  std::cout << "initialized an npc" << std::endl;
}

void NPC_Component::update(TransformComponent& self, TransformComponent& player){
  if(Game::map->scrolled_x){
    self.movement_speed_x = self.base_speed_x - player.movement_speed_x;
  }
  else{
    self.movement_speed_x = self.base_speed_x;
  }
  if(Game::map->scrolled_y){
    self.movement_speed_y = self.base_speed_y - player.movement_speed_y;
  }
  else{
    self.movement_speed_y = self.base_speed_y;
  }
  switch (type) {
    case NPC_ENEMY:
      attackPlayer(self, player);
      break;
    case NPC_NEUTRAL:
      randomMovement();
      break;
  }
}

void NPC_Component::attackPlayer(TransformComponent& self, TransformComponent& player){
  if(self.dst_rect.x + self.dst_rect.w > player.dst_rect.x){
    self.move(-1,0);
  }
  if(self.dst_rect.x < player.dst_rect.x + player.dst_rect.w ){
    self.move(1,0);
  }
  if(self.dst_rect.y + self.dst_rect.h > player.dst_rect.y){
    self.move(0,-1);
  }
  if(self.dst_rect.y < player.dst_rect.y + player.dst_rect.h ){
    self.move(0,1);
  }
}

void NPC_Component::randomMovement(){}
