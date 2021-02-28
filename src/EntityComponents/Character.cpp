#include "Character.h"

void AttackPlayer(TransformComponent &self_transform, TransformComponent &player_transform){
  if(self_transform.destination_rect.x > player_transform.destination_rect.x + 80){
    self_transform.destination_rect.x--;
  }
  if(self_transform.destination_rect.x < player_transform.destination_rect.x - 80){
    self_transform.destination_rect.x++;
  }
  if(self_transform.destination_rect.y > player_transform.destination_rect.y + 80){
    self_transform.destination_rect.y--;
  }
  if(self_transform.destination_rect.y < player_transform.destination_rect.y - 80){
    self_transform.destination_rect.y++;
  }
}
