#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(char* texturesheet, SDL_Rect dstrect, int actual_width, int actual_height, int sprite_amount)
: destination_rect(dstrect), actual_width(actual_width), actual_height(actual_width), sprite_amount(sprite_amount){
  texture = TextureManager::load_texture(texturesheet);
}

GameObject::~GameObject(){}

void GameObject::render(){
  SDL_RenderCopy(Game::renderer, texture, &source_rect, &destination_rect);
}

void GameObject::update(){
  source_rect = {32*current_sprite,0,actual_width,actual_height};
  current_sprite++;
  if(current_sprite==sprite_amount){
    current_sprite = 0;
}
}

void GameObject::move(int x_diff, int y_diff){
  destination_rect.x += x_diff;
  destination_rect.y += y_diff;
}
