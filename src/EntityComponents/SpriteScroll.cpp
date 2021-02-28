#include "SpriteScroll.h"

void System_SpriteScroll(SpriteScroll &info, SDL_Rect &source_rect){
  source_rect = {32*info.current_sprite_x,32*info.current_sprite_y,info.sprite_height,info.sprite_height};

  if(info.x_scrolls){
    info.current_sprite_x++;
  }

  if(info.y_scrolls){
    info.current_sprite_y++;
  }

  if(info.current_sprite_x==info.max_sprites_x){
    info.current_sprite_x = 0;
  }
  if(info.current_sprite_y==info.max_sprites_y){
    info.current_sprite_y=0;
    info.y_scrolls = false;
  }
}
