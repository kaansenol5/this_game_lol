#pragma once
#include "Transform.h"

struct CharacterComponent{
  bool is_enemy;
  bool is_neutral;
};

void AttackPlayer(TransformComponent &self_transform, TransformComponent &player_transform);
void Update(CharacterComponent info);
