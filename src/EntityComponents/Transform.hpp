#pragma once
#include <SDL2/SDL.h>

class TransformComponent{
public:
  TransformComponent(int x, int y, int width, int height, char* directory, int speed, int real_w, int real_h);
  int x;
  int y;
  int width;
  int height;
  char* directory;
  void render();
  void animate_sprites();
  void move(int x_diff, int y_diff);
private:
  SDL_Rect src_rect;
  SDL_Rect dst_rect;
  int movement_speed;
  int real_w;
  int real_h;
  SDL_Texture* texture;
};
