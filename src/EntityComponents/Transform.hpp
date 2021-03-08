#pragma once
#include <SDL2/SDL.h>
#include <string>
class TransformComponent{
public:
  TransformComponent(int x, int y, int width, int height, std::string texture_file, int speed_x, int speed_y, int real_w, int real_h, bool animated, int sprite_amnt_x, int sprite_amnt_y, bool x_scrolls, bool y_scrolls);
  ~TransformComponent();
  void render();
  void animate_sprites();
  void move(int x_diff, int y_diff);
  SDL_Rect dst_rect;
  int base_speed_x;
  int base_speed_y;
  int movement_speed_x;
  int movement_speed_y;
private:
  SDL_Rect src_rect;
  int real_w;
  int real_h;
  bool animated;
  int sprite_amnt_x;
  int sprite_amnt_y;
  bool x_scrolls;
  bool y_scrolls;
  int current_sprite_x = 0;
  int current_sprite_y = 0;
  SDL_Texture* texture;
};
