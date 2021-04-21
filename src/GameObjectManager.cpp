#include "GameObjectManager.hpp"
#include "JsonLoader.hpp"
#include "SDL_rect.h"
#include "TextureManager.hpp"
#include "EntityComponents/Player.hpp"
#include "EntityComponents/NPC.hpp"
#include "EntityComponents/TransformComponent.hpp"
#include "EntityComponents/Projectile.hpp"
#include "EntityComponents/Hitbox.hpp"
#include <string>


entt::registry GameObjectManager::EntityRegistry;

GameObjectManager::GameObjectManager(){
    EntityRegistry = entt::registry();
    config = JsonLoader::load((char*)"config/characters.json");
    unsigned character_variation_amount = config["character_variation_amount"];

    for(unsigned i = 0; i <= character_variation_amount; i++){
        std::string asset = config[std::to_string(i)]["sprite"];
        SDL_Texture* texture = TextureManager::load_image(asset.c_str());
        textures.push_back (texture);
    }
    std::cout << "Game sucsessfully loaded most textures" << std::endl;
}



GameObjectManager::~GameObjectManager(){
  for(SDL_Texture* texture : textures){
    SDL_DestroyTexture(texture);
  }
  std::cout << "GameObjectManager.cpp goes bye-bye" << std::endl;
}

void GameObjectManager::update_all(){
  EntityRegistry.view<NPC_Component>().each([](entt::entity id, NPC_Component& component){
    component.update();
  });
  EntityRegistry.view<Projectile>().each([](entt::entity id, Projectile& projectile){
    projectile.update();
  });
}

void GameObjectManager::shoot_projectile(int tag, SDL_Rect location, int x_direction, int y_direction, unsigned range){
  entt::entity spawned = spawn(tag, location.x, location.y);
  EntityRegistry.emplace<Projectile>(spawned, location, x_direction, y_direction, range);
  EntityRegistry.emplace<Hitbox>(spawned);
}

void GameObjectManager::render_all(){
    auto view = EntityRegistry.view<TransformComponent>();
    for(entt::entity id : view){
      TransformComponent& transform = view.get<TransformComponent>(id);
      transform.render();
    }
}



void GameObjectManager::move_all(int x, int y){
  EntityRegistry.view<TransformComponent>().each([x, y](auto entity, auto &transform_comp){
    if( !GameObjectManager::EntityRegistry.has<Player>(entity) ){
      transform_comp.move(x,y,false);
    }
  });
}

void GameObjectManager::spawn_player(int x, int y){
    spawn(0, x, y);
}


entt::entity GameObjectManager::spawn(int tag, int x, int y){
    entt::entity spawned = EntityRegistry.create();
    auto current_conf = config[std::to_string(tag)];
    
    EntityRegistry.emplace<TransformComponent>(spawned, x, y, current_conf["width"], current_conf["height"], current_conf["real_sprite_width"], current_conf["real_sprite_height"], current_conf["animated"], current_conf["x_animations"], current_conf["y_animations"], textures[tag], current_conf["movement_speed_x"]);
    if(current_conf["type"] == "npc"){
      EntityRegistry.emplace<NPC_Component>(spawned, current_conf["npc_type"]);
    }
    else if(current_conf["type"] == "player"){
      EntityRegistry.emplace<Player>(spawned);
      EntityRegistry.emplace<Hitbox>(spawned);
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

