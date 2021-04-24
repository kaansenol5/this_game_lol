#include "../TextureManager.hpp"
#include "TransformComponent.hpp"
TransformComponent::TransformComponent(int x, int y, int w, int h, bool filled) : filled(filled){
    color = {0,0,0,0};
    destination_rect = {x,y,w,h};
}

void TransformComponent::render(){
    TextureManager::draw_rect(&destination_rect, filled, color);
}

void TransformComponent::move(int xd, int yd){
    destination_rect.x += xd;
    destination_rect.y += yd;
}