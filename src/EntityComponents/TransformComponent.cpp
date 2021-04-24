#include "../TextureManager.hpp"
#include "TransformComponent.hpp"
#include "SpeedComponent.h"
TransformComponent::TransformComponent(int x, int y, int w, int h, bool filled) : filled(filled){
    color = {0,0,0,0};
    destination_rect = {x,y,w,h};
}

void TransformComponent::render(){
    TextureManager::draw_rect(&destination_rect, filled, color);
}

void TransformComponent::move(int xd, int yd){
    entt::entity this_entity = entt::to_entity(GameObjectManager::EntityRegistry, *this);
    if(GameObjectManager::EntityRegistry.has<SpeedComponent>(this_entity)){
        SpeedComponent& speed = GameObjectManager::EntityRegistry.get<SpeedComponent>(this_entity);
        xd *= speed.current_movement_speed;
        yd *= speed.current_movement_speed; 
    }
    destination_rect.x += xd;
    destination_rect.y += yd;
}