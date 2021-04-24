#include "NPCComponent.hpp"
#include <iostream>
#include <string>
#include "../GameObjectManager.hpp"
#include "../include/entt.hpp"
#include "TransformComponent.hpp"
#include "../SceneManager.hpp"
#include "Player.hpp"
NPCComponent::NPCComponent(std::string type)
:type(type){

}

void NPCComponent::update(){
  if(type == "enemy")
      attackPlayer();
  if(type == "neutral")
      randomMovement();
  }


void NPCComponent::attackPlayer(){
  entt::entity id = entt::to_entity(GameObjectManager::EntityRegistry, *this);
  TransformComponent& transform_comp = GameObjectManager::EntityRegistry.get<TransformComponent>(id);
  entt::entity player = GameObjectManager::get_unique_entity_id<Player>();
  TransformComponent& player_transform = GameObjectManager::EntityRegistry.get<TransformComponent>(player);
  if(transform_comp.destination_rect.x < SceneManager::width + 300 && transform_comp.destination_rect.x > -300 - transform_comp.destination_rect.w  && transform_comp.destination_rect.y < SceneManager::height + 300 && transform_comp.destination_rect.y > -300 - transform_comp.destination_rect.h){
    if(transform_comp.destination_rect.x + transform_comp.destination_rect.w > player_transform.destination_rect.x){
      transform_comp.move(-1,0);
    }
    if(transform_comp.destination_rect.x < player_transform.destination_rect.x + player_transform.destination_rect.w ){
      transform_comp.move(1,0);
    }
    if(transform_comp.destination_rect.y + transform_comp.destination_rect.h > player_transform.destination_rect.y){
      transform_comp.move(0,-1);
    }
    if(transform_comp.destination_rect.y < player_transform.destination_rect.y + player_transform.destination_rect.h ){
      transform_comp.move(0,1);
    }
  }

}

void NPCComponent::randomMovement(){}
