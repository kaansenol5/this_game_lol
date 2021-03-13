#pragma once
#include <SDL2/SDL.h>
#include <string>
class TransformComponent{
public:
  TransformComponent(int x, int y, int width, int height, SDL_Texture* texture, int speed_x, int speed_y, int real_w, int real_h, bool animated, int sprite_amnt_x, int sprite_amnt_y, bool x_scrolls, bool y_scrolls);
  ~TransformComponent();
  void render();
  void animate_sprites();
  void move(int x_diff, int y_diff, bool withSpeed);
  SDL_Rect dst_rect;
  unsigned short base_speed_x;
  unsigned short base_speed_y;
  unsigned short movement_speed_x;
  unsigned short movement_speed_y;
private:
  SDL_Texture* texture;
  SDL_Rect src_rect;
  unsigned short real_w;
  unsigned short real_h;
  bool animated;
  unsigned short sprite_amnt_x;
  unsigned short sprite_amnt_y;
  bool x_scrolls;
  bool y_scrolls;
  unsigned short current_sprite_x = 0;
  unsigned short current_sprite_y = 0;
};
