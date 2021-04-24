#include "GameObjectManager.hpp"
#include "JsonLoader.hpp"
#include "SDL_rect.h"
#include "TextureManager.hpp"
#include "EntityComponents/Player.hpp"
#include "EntityComponents/NPC.hpp"
#include "EntityComponents/TransformComponent.hpp"
#include "EntityComponents/ProjectileComponent.hpp"
#include "EntityComponents/Hitbox.hpp"
#include "EntityComponents/TextureComponent.hpp"
#include "EntityComponents/SpeedComponent.h"
#include <string>


entt::registry GameObjectManager::EntityRegistry;

GameObjectManager::GameObjectManager(){
    EntityRegistry = entt::registry();
}



GameObjectManager::~GameObjectManager(){
  std::cout << "GameObjectManager.cpp goes bye-bye" << std::endl;
}

void GameObjectManager::update_all(){
  EntityRegistry.view<NPC_Component>().each([](entt::entity id, NPC_Component& component){
    component.update();
  });
  EntityRegistry.view<ProjectileComponent>().each([](entt::entity id, ProjectileComponent& projectile){
    projectile.update();
  });
}

void GameObjectManager::shoot_projectile(int tag, SDL_Rect location, int x_direction, int y_direction, unsigned range){
  entt::entity spawned = spawn({"projectiles"},tag, location.x, location.y);
  EntityRegistry.emplace<ProjectileComponent>(spawned, location, x_direction, y_direction, range);
  EntityRegistry.emplace<Hitbox>(spawned);
}

void GameObjectManager::render_all(){
    auto view = EntityRegistry.view<TextureComponent>();
    for(entt::entity id : view){
      TextureComponent& texturecomp = view.get<TextureComponent>(id);
      texturecomp.render();
    }
}



void GameObjectManager::move_all(int x, int y){
  EntityRegistry.view<TransformComponent>().each([x, y](auto entity, auto &transform_comp){
    if( !GameObjectManager::EntityRegistry.has<Player>(entity) ){
      transform_comp.move(x,y);
    }
  });
}

void GameObjectManager::spawn_player(int x, int y){
    entt::entity spawned = spawn({"characters", "players"}, 0, x, y);
    EntityRegistry.emplace<Player>(spawned);
}


entt::entity GameObjectManager::spawn(std::vector<std::string> entity_class, int entity_tag, int x, int y){
    entt::entity spawned = EntityRegistry.create();
    EntityList list((char*)"config/characters.json", entity_class);
    json character = list.get_character(entity_tag);

    if(list.check_existence<json>(entity_tag, "TransformComponent")){
      EntityRegistry.emplace<TransformComponent>(spawned, x, y, character["TransformComponent"]["width"], character["TransformComponent"]["height"]);
    }
    if(list.check_existence<json>(entity_tag, "TextureComponent")){
      std::string file = character["TextureComponent"]["texture"];
      SDL_Texture* entity_texture = TextureManager::load_or_get_image_texture(file.c_str());
      EntityRegistry.emplace<TextureComponent>(spawned, entity_texture, character["TextureComponent"]["x_animation_count"], character["TextureComponent"]["y_animation_count"], character["TextureComponent"]["width"], character["TextureComponent"]["height"]);
    }
    if(list.check_existence<int>(entity_tag, "movement_speed")){
      EntityRegistry.emplace<SpeedComponent>(spawned, character["movement_speed"]);
    }
    
    return spawned;
}


entt::entity GameObjectManager::check_collision_with_any(SDL_Rect rect){
  auto hitbox_entities = EntityRegistry.view<Hitbox>();
  for(auto id : hitbox_entities){
    TransformComponent transform = EntityRegistry.get<TransformComponent>(id);
    SDL_Rect &hitbox_loc = transform.destination_rect;
    if(rect.x > hitbox_loc.x && rect.x < hitbox_loc.x + hitbox_loc.w){
      if(rect.y > hitbox_loc.y && rect.y < hitbox_loc.y + hitbox_loc.h){
        return id;
      }
    }
  }
  return entt::null;
}


