#pragma once
#include <SDL2/SDL.h>

class GameObject{
public:
  GameObject(char* texturesheet, SDL_Rect dstrect, int actual_width, int actual_height, int sprite_amount);
  virtual ~GameObject();
  virtual void update();
  virtual void render();
  SDL_Rect destination_rect; //this is x, y, width, height. it defines where this object will be printed on and will be used by Render()
  SDL_Rect source_rect; //this is x,y,w,h of the texture file. it defines which part of the texture will be printed. NULL = entire texture
  void move(int x_diff, int y_diff);
  SDL_Texture* texture;
  int sprite_amount;
  int actual_width;
  int actual_height;
private:
  int current_sprite = 0;
};
