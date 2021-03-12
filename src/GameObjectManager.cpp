#include "GameObjectManager.hpp"
#include "TextureManager.hpp"
#include "EntityComponents/Player.h"
#include "EntityComponents/Hitbox.h"
#include <string>

/*
THIS READS characters.json TO GET ALL INFO ABOUT EVERYTHING RENDERED EXCEPT MAP TILES IN THE GAME
THE IDENTIFIER OF THE PLAYER IN JSON FILE IS ALWAYS 0
*/


GameObjectManager::GameObjectManager(){
  config = JsonLoader::load((char*)"config/characters.json");
  unsigned character_variation_amount = config["character_variation_amount"];
  for(unsigned i = 0; i<character_variation_amount; i++){
    SDL_Texture* texture = TextureManager::load_texture(config[std::to_string(i)]["sprite"]);
    textures.push_back(texture);
  }
}

void GameObjectManager::spawn(int tag, int x, int y){
  auto spawned = Game::EntityRegistry.create();
  std::string tagstr = std::to_string(tag);
  auto current_conf = config[tagstr];
  Game::EntityRegistry.emplace<TransformComponent>(spawned, x, y, current_conf["width"],current_conf["height"],textures[tag], current_conf["movement_speed_x"], current_conf["movement_speed_y"], current_conf["real_sprite_width"], current_conf["real_sprite_height"], current_conf["animated"], current_conf["x_animations"], current_conf["y_animations"], current_conf["x_animated"], current_conf["y_animated"]);
  if(current_conf["is_npc"]){
    Game::EntityRegistry.emplace<NPC_Component>(spawned, current_conf["npc_type"]);
  }
  if(current_conf["type"] == "player"){
    Game::EntityRegistry.emplace<Player>(spawned);
  }
  if(current_conf["type"] == "landresource"){
   Game::EntityRegistry.emplace<Hitbox>(spawned);
  }
}

void GameObjectManager::enemy_spawn_random(){
  spawn(rand()%(int)config["enemy_variation_amount"]+1, (rand()%Game::Width+200)-200, (rand()%Game::Height+200)-200);
}

void GameObjectManager::landresource_spawn_random(int mapsize){
  int entity_type = (rand()%(int)config["landresource_variation_amount"])+(int)config["enemy_variation_amount"]+(int)config["neutral_variation_amount"]+1;
  spawn(entity_type, rand() % mapsize, rand()% mapsize);
}

void GameObjectManager::update(){
  Game::EntityRegistry.group<NPC_Component, TransformComponent>().each([](auto entity, auto &npc_comp, auto &transform_comp){
    Game::EntityRegistry.view<Player>().each([&npc_comp, &transform_comp](auto player, auto &player_comp){
      npc_comp.update(transform_comp, Game::EntityRegistry.get<TransformComponent>(player));
    });

    if(transform_comp.dst_rect.x + Game::Width < 500 || transform_comp.dst_rect.y + Game::Height < 500 || transform_comp.dst_rect.x + Game::Width > 2*Game::Width+500 || transform_comp.dst_rect.y + Game::Height > 2*Game::Height+500){
      Game::EntityRegistry.destroy(entity);
      std::cout << "killed an innocent npc" << std::endl;
    }
    });
}

void GameObjectManager::render_all(){
  Game::EntityRegistry.view<TransformComponent>().each([](auto entity, auto &transform_comp){
    transform_comp.render();
  });
}

void GameObjectManager::move_all(int x, int y){
  Game::EntityRegistry.view<TransformComponent>().each([x, y](auto entity, auto &transform_comp){
    if(!Game::EntityRegistry.has<Player>(entity)){
      transform_comp.move(x,y,false);
    }
  });
}
