#include <string>
#include <SDL2/SDL.h>
#include "Transform.h"

struct Player{
  std::string name = "Bruh";
};


void KeyHandle(const Uint8 *state, TransformComponent &transform);
