#include "Transform.h"
#include <SDL2/SDL.h>

void render(SDL_Renderer* renderer, TransformComponent Transform){
  SDL_RenderCopy(renderer, Transform.texture, &Transform.source_rect, &Transform.destination_rect);
}
