#include "Character.h"
#include <iostream>

void AttackPlayer(TransformComponent &self_transform, TransformComponent &player_transform){
  std::cout << self_transform.x_on_map << " x " << player_transform.x_on_map << std::endl;
  std::cout << self_transform.y_on_map << " y " << player_transform.y_on_map << std::endl;
  if(self_transform.x_on_map > player_transform.x_on_map + 80){
    self_transform.x_on_map--;
  }
  if(self_transform.x_on_map < player_transform.x_on_map- 80){
    self_transform.x_on_map++;
  }
  if(self_transform.y_on_map > player_transform.y_on_map + 80){
    self_transform.y_on_map--;
  }
  if(self_transform.y_on_map < player_transform.y_on_map - 80){
    self_transform.y_on_map++;
  }
}
