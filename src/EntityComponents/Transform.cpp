#include "Transform.hpp"
#include "../TextureManager.hpp"
#include "../Game.hpp"
#include <iostream>
TransformComponent::TransformComponent(int x, int y, int width, int height, std::string directory, int speed, int real_w, int real_h, bool animated, int sprite_amnt_x, int sprite_amnt_y, bool x_scrolls, bool y_scrolls)
:  movement_speed(speed), real_w(real_w), real_h(real_h), animated(animated), sprite_amnt_x(sprite_amnt_x), sprite_amnt_y(sprite_amnt_y), x_scrolls(x_scrolls), y_scrolls(y_scrolls){
  texture = TextureManager::load_texture((char*)directory.c_str());
  std::cout << sizeof(texture) << std::endl;
  src_rect = {0,0,real_w, real_h};
  dst_rect = {x, y, real_w, real_h};
}

TransformComponent::~TransformComponent(){
  SDL_DestroyTexture(texture);
}

void TransformComponent::render(){
  if(animated){
    animate_sprites();
  }
  TextureManager::render(texture, src_rect, dst_rect);
}

void TransformComponent::animate_sprites(){
  src_rect = {real_w*current_sprite_x,real_h*current_sprite_y,real_w,real_h};

  if(x_scrolls){
    current_sprite_x++;
  }

  if(y_scrolls){
    current_sprite_y++;
  }

  if(current_sprite_x==sprite_amnt_x){
    current_sprite_x = 0;
  }
  if(current_sprite_y==sprite_amnt_y){
    current_sprite_y=0;
    y_scrolls = false;
  }
}

void TransformComponent::move(int x_diff, int y_diff){
  dst_rect.x += x_diff;
  dst_rect.y += y_diff;
}
