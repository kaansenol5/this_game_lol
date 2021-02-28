#include <SDL2/SDL_rect.h>
struct SpriteScroll{
  int max_sprites_x;
  int max_sprites_y;
  int current_sprite_x;
  int current_sprite_y;
  int sprite_width;
  int sprite_height;
  bool x_scrolls;
  bool y_scrolls;
};

void System_SpriteScroll(SpriteScroll &info, SDL_Rect &source_rect);
