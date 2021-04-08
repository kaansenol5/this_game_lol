#include "NPC.hpp"
#include <iostream>
#include "../GameObjectManager.hpp"
#include "../include/entt.hpp"
#include "TransformComponent.hpp"

NPC_Component::NPC_Component(Type type)
:type(type){

}

void NPC_Component::update(){
  switch (type) {
    case ENEMY:
      attackPlayer();
      break;
    case NEUTRAL:
      randomMovement();
      break;
  }
}

void NPC_Component::attackPlayer(){
  entt::entity id = entt::to_entity(GameObjectManager::EntityRegistry, this);
  TransformComponent& transform_comp = GameObjectManager::EntityRegistry.get<TransformComponent>(id);

  if(transform_comp.destination_rect.x < SceneManager::width + 300 && transform_comp.destination_rect.x > -300 - transform_comp.destination_rect.w  && transform_comp.destination_rect.y < SceneManager::height + 300 && transform_comp.destination_rect.y > -300 - transform_comp.destination_rect.h){
    if(transform_comp.destination_rect.x + transform_comp.destination_rect.w > transform_comp.destination_rect.x){
      transform_comp.move(-1,0, true);
    }
    if(transform_comp.destination_rect.x < transform_comp.destination_rect.x + transform_comp.destination_rect.w ){
      transform_comp.move(1,0, true);
    }
    if(transform_comp.destination_rect.y + transform_comp.destination_rect.h > transform_comp.destination_rect.y){
      transform_comp.move(0,-1, true);
    }
    if(transform_comp.destination_rect.y < transform_comp.destination_rect.y + transform_comp.destination_rect.h ){
      transform_comp.move(0,1, true);
    }
  }

}

void NPC_Component::randomMovement(){}
