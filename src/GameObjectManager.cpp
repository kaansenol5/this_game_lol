#include "GameObjectManager.hpp"
#include "JsonLoader.hpp"
#include "TextureManager.hpp"
#include "EntityComponents/Player.hpp"
#include "EntityComponents/NPC.hpp"
#include "EntityComponents/TransformComponent.hpp"
#include <string>


entt::registry GameObjectManager::EntityRegistry;

GameObjectManager::GameObjectManager(){
    EntityRegistry = entt::registry();
    config = JsonLoader::load((char*)"config/characters.json");
    unsigned character_variation_amount = config["character_variation_amount"];

    for(unsigned i = 0; i < character_variation_amount; i++){
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

}

void GameObjectManager::render_all(){
    EntityRegistry.view<TransformComponent>().each([](auto entity, TransformComponent& component){
        component.render();
     });
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
    std::string tagstr = std::to_string(tag);
    auto current_conf = config[tagstr];
    EntityRegistry.emplace<TransformComponent>(spawned, x, y, current_conf["width"], current_conf["height"], current_conf["real_sprite_width"], current_conf["real_sprite_height"], current_conf["animated"], current_conf["x_animations"], current_conf["y_animations"], textures[tag], current_conf["movement_speed_x"]);
    if(current_conf["type"] == "npc"){
      EntityRegistry.emplace<NPC_Component>(spawned, current_conf["npc_type"]);
    }
    else if(current_conf["type"] == "player"){
      EntityRegistry.emplace<Player>(spawned);
    }
    return spawned;
}


