#pragma once
#include "Transform.hpp"
#include "Hitbox.h"
#include "../TextureManager.hpp"
#include "../Game.hpp"
#include <iostream>
TransformComponent::TransformComponent(int x, int y, int width, int height, SDL_Texture* texture, int speed_x, int speed_y, int real_w, int real_h, bool animated, int sprite_amnt_x, int sprite_amnt_y, bool x_scrolls, bool y_scrolls)
:  base_speed_x(speed_x), base_speed_y(speed_y),texture(texture), real_w(real_w), real_h(real_h), animated(animated), sprite_amnt_x(sprite_amnt_x), sprite_amnt_y(sprite_amnt_y), x_scrolls(x_scrolls), y_scrolls(y_scrolls){

  src_rect = {0,0,real_w, real_h};
  dst_rect = {x, y, width, height};
  movement_speed_x = base_speed_x;
  movement_speed_y = base_speed_y;
}

TransformComponent::~TransformComponent(){
  
}


void TransformComponent::render(){
  if(animated){
    animate_sprites();
  }
  /*
  SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
  SDL_RenderDrawRect(Game::renderer, &dst_rect);
  SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
  */
  TextureManager::render(texture, &src_rect, &dst_rect);
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

void TransformComponent::move(int x_diff, int y_diff, bool withSpeed){
  if(withSpeed){
    bool allow_x=true;
    bool allow_y=true;
    Game::EntityRegistry.view<Hitbox, TransformComponent>().each([this, x_diff, y_diff, &allow_x, &allow_y](auto ent, auto &hitbox, auto &transform_comp){
      if(((dst_rect.x + x_diff*movement_speed_x > transform_comp.dst_rect.x && dst_rect.x + x_diff*movement_speed_x < transform_comp.dst_rect.x + transform_comp.dst_rect.w) && (dst_rect.y > transform_comp.dst_rect.y && dst_rect.y < transform_comp.dst_rect.y + transform_comp.dst_rect.h))){
        allow_x=false;
      }
      else if(((dst_rect.y + y_diff*movement_speed_y > transform_comp.dst_rect.y && dst_rect.y + y_diff*movement_speed_y < transform_comp.dst_rect.y + transform_comp.dst_rect.h) && (dst_rect.x > transform_comp.dst_rect.x && dst_rect.x < transform_comp.dst_rect.x + transform_comp.dst_rect.w))){
        allow_y=false;
      }

    });
    if(allow_x)
      dst_rect.x += x_diff*movement_speed_x;
    if(allow_y)
      dst_rect.y += y_diff*movement_speed_y;

  }
  else{
    dst_rect.x += x_diff;
    dst_rect.y += y_diff;
  }
}
