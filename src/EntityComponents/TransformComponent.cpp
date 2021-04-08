#include "TransformComponent.hpp"

TransformComponent::TransformComponent(int x, int y, int w, int h, int real_w, int real_h, bool is_animated, int x_animation_count, int y_animation_count, SDL_Texture* texture, int speed)
: real_width(real_w), real_height(real_h), is_animated(is_animated), x_animation_count(x_animation_count), y_animation_count(y_animation_count), texture(texture), base_speed(speed){
    destination_rect = {x, y, w, h};
    source_rect = {0, 0, real_w, real_h};
    current_speed = base_speed; 
}

void TransformComponent::render(){
    if (is_animated){
        animate();
    }

    TextureManager::render(texture, &source_rect, &destination_rect);
}

void TransformComponent::animate(){
  source_rect = {real_width * current_sprite_x, real_height * current_sprite_y, real_width, real_height};

  if(x_animate){
    current_sprite_x++;
  }

  if(y_animate){
    current_sprite_y++;
  }

  if(current_sprite_x==x_animation_count){
    current_sprite_x = 0;
  }
  if(current_sprite_y==y_animation_count){
    current_sprite_y=0;
    y_animate = false;
  }
}

void TransformComponent::move(int x_diff, int y_diff, bool with_speed){
    if (with_speed){
        destination_rect.x += x_diff * current_speed;
        destination_rect.y += y_diff * current_speed; 
    }
    else{
        destination_rect.x += x_diff;
        destination_rect.y += y_diff; 
    }
}