#include "Transform.hpp"
#include "../TextureManager.hpp"
#include "../Game.hpp"

TransformComponent::TransformComponent(int x, int y, int width, int height, char* directory, int speed, int real_w, int real_h)
: x(x), y(y), width(width), height(height), movement_speed(speed), real_w(real_w), real_h(real_h){
  texture = TextureManager::load_texture(directory);
  src_rect = {0,0,real_w, real_h};
  dst_rect = {300, 300, real_w, real_h};
}

void TransformComponent::render(){
  TextureManager::render(texture, src_rect, dst_rect);
}
