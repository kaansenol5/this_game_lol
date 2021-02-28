#include <SDL2/SDL.h>

struct TransformComponent{
  unsigned long x_on_map;
  unsigned long y_on_map;
  SDL_Rect source_rect;
  SDL_Rect destination_rect;
  SDL_Texture* texture;
};

void render(SDL_Renderer* renderer, TransformComponent Transform);
