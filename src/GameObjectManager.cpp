#include "GameObjectManager.hpp"
#include "TextureManager.hpp"
#include "EntityComponents/Player.h"
#include "EntityComponents/Hitbox.h"
#include <string>

/*
THE IDENTIFIER OF THE PLAYER IN JSON FILE IS ALWAYS 0, if it isnt, things will break.
*/


GameObjectManager::GameObjectManager(int width, int height) : width(width), height(height){
  config = JsonLoader::load((char*)"config/characters.json");
  unsigned character_variation_amount = config["character_variation_amount"];
  for(unsigned i = 0; i<character_variation_amount; i++){
    SDL_Texture* texture = TextureManager::load_texture(config[std::to_string(i)]["sprite"]);
    textures.push_back(texture);
  }
}

GameObjectManager::~GameObjectManager(){
  for(SDL_Texture* texture : textures){
    SDL_DestroyTexture(texture);
  }
  std::cout << "GameObjectManager.cpp goes bye-bye" << std::endl;
}

void GameObjectManager::spawn(int tag, int x, int y){
  auto spawned = EntityRegistry.create();
  std::string tagstr = std::to_string(tag);
  auto current_conf = config[tagstr];
  EntityRegistry.emplace<TransformComponent>(spawned, x, y, current_conf["width"],current_conf["height"],textures[tag], current_conf["movement_speed_x"], current_conf["movement_speed_y"], current_conf["real_sprite_width"], current_conf["real_sprite_height"], current_conf["animated"], current_conf["x_animations"], current_conf["y_animations"], current_conf["x_animated"], current_conf["y_animated"]);
  if(current_conf["is_npc"]){
    EntityRegistry.emplace<NPC_Component>(spawned, current_conf["npc_type"], width, height);
  }
  if(current_conf["type"] == "player"){
    EntityRegistry.emplace<Player>(spawned);
  }
  if(current_conf["type"] == "landresource"){
   EntityRegistry.emplace<Hitbox>(spawned);
  }
}

void GameObjectManager::enemy_spawn_random(int width, int height){
  spawn(rand()%(int)config["enemy_variation_amount"]+1, (rand()%width+200)-200, (rand()%height+200)-200);
}

void GameObjectManager::landresource_spawn_random(int mapsize, int tilesize){
  int entity_type = (rand()%(int)config["landresource_variation_amount"])+(int)config["enemy_variation_amount"]+(int)config["neutral_variation_amount"]+1;
  int x = rand() % mapsize;
  int y = rand()% mapsize;
  x -= x % tilesize;
  y -= y % tilesize;
  spawn(entity_type, x, y);
}

void GameObjectManager::update(int width, int height){
  EntityRegistry.group<NPC_Component, TransformComponent>().each([this, width, height](auto entity, auto &npc_comp, auto &transform_comp){
    EntityRegistry.view<Player>().each([&npc_comp, &transform_comp, this](auto player, auto &player_comp){
      npc_comp.update(transform_comp, EntityRegistry.get<TransformComponent>(player), EntityRegistry);
    });

    if(transform_comp.dst_rect.x + width < 500 || transform_comp.dst_rect.y + height < 500 || transform_comp.dst_rect.x + width > 2*width+500 || transform_comp.dst_rect.y + height > 2*height+500){
      EntityRegistry.destroy(entity);
    }
    });
}

void GameObjectManager::render_all(){
  EntityRegistry.view<TransformComponent>().each([](auto entity, auto &transform_comp){
    transform_comp.render();
  });
}

void GameObjectManager::move_all(int x, int y){
  EntityRegistry.view<TransformComponent>().each([x, y, this](auto entity, auto &transform_comp){
    if(!EntityRegistry.has<Player>(entity)){
      transform_comp.move(x,y,false, EntityRegistry);
    }
  });
}
