#pragma once
#include <SDL2/SDL.h>
#include <string>
class TransformComponent{
public:
  TransformComponent(int x, int y, int width, int height, std::string directory, int speed, int real_w, int real_h, bool animated, int sprite_amnt_x, int sprite_amnt_y, bool x_scrolls, bool y_scrolls);
  ~TransformComponent();
  char* directory;
  void render();
  void animate_sprites();
  void move(int x_diff, int y_diff);
  int movement_speed;
  SDL_Rect dst_rect;
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
  int max_sprites_x;
  int max_sprites_y;
  SDL_Texture* texture;
};
