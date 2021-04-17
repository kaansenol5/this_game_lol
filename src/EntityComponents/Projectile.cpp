#include "Projectile.hpp"
#include "SDL_rect.h"
#include "../include/entt.hpp"
#include "../GameObjectManager.hpp"
#include "../TextureManager.hpp"
#include "TransformComponent.hpp"
#include <iostream>

Projectile::Projectile(SDL_Rect start_loc, int target_x, int target_y, unsigned range) 
:start_loc(start_loc) ,range(range), target_x(target_x), target_y(target_y) {
    m = (double)(target_y - start_loc.y) / (double)(target_x - start_loc.x);
    std::cout << m << std::endl;
    if(start_loc.x - target_x > 0){
        x_direction = -1;
    }
    else{
        x_direction = 1;
    }
    if(start_loc.y - target_y > 0){
        y_direction = -1;
    }
    else {
        y_direction = 1;
    }
    if(abs(m) > 1){
        x_direction = 0;
        y_move = true;
    }
    else {
        y_direction = 0;
        y_move = false;
    }
}

void Projectile::update(){
    entt::entity this_entity = entt::to_entity(GameObjectManager::EntityRegistry, *this);
    TransformComponent& transform_comp = GameObjectManager::EntityRegistry.get<TransformComponent>(this_entity);
    transform_comp.move(x_direction, y_direction);
    if (y_move)
        transform_comp.destination_rect.x = target_x - 1 / m * (target_y - transform_comp.destination_rect.y);
    else
        transform_comp.destination_rect.y =  (target_y - m*(target_x - transform_comp.destination_rect.x));

    moved_for_frames++;
    if(moved_for_frames >= range){
        GameObjectManager::EntityRegistry.destroy(this_entity);
    }
}

