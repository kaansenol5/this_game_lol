#include "Game.hpp"
#include <iostream>
#include <ctime>
#include "EntityComponents/Transform.h"
#include "EntityComponents/Character.h"
#include "EntityComponents/SpriteScroll.h"
#include "EntityComponents/Player.h"

int Game::Width = 0;
int Game::Height = 0;
SDL_Renderer* Game::renderer = nullptr;
bool Game::running = true;
entt::entity Game::player = entt::null;

Game::Game(){
  SDL_Init(SDL_INIT_EVERYTHING);
  Width = 1920;
  Height = 1080;
  Title = "NukeTown";
  TTF_Init();
  window = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //create renderer
  SDL_SetRenderDrawColor(renderer, 255,255,255,255); //set default rendering color to white (rgba)
  running=true;
  player = EntityRegistry.create();
  EntityRegistry.emplace<TransformComponent>(player, 0,0,0,0,32,32,Width/2,Height/2,128,128,TextureManager::load_texture("assets/sprites/wizard.png"),6);
  EntityRegistry.emplace<CharacterComponent>(player);
  EntityRegistry.emplace<SpriteScroll>(player,3,1,0,0,32,32,true,false);
  EntityRegistry.emplace<Player>(player);
  randomEnemySpawning();
  game_map = new Map();
}



void Game::updateFrame(int i){
  SDL_RenderClear(renderer);
  game_map->render();
  auto renderable = EntityRegistry.view<TransformComponent>();
  for(auto entity : renderable){
    TransformComponent &Transform = renderable.get<TransformComponent>(entity);
    render(renderer, Transform);
  }
  auto characters = EntityRegistry.view<CharacterComponent>();
  for(auto entity : characters){
    CharacterComponent &component = characters.get<CharacterComponent>(entity);
    if(component.is_enemy){
      AttackPlayer(EntityRegistry.get<TransformComponent>(entity), EntityRegistry.get<TransformComponent>(player));
    }
  }
  auto scrolling_entities = EntityRegistry.view<SpriteScroll>();
  for(auto entity : scrolling_entities){
    SpriteScroll &scroll = scrolling_entities.get<SpriteScroll>(entity);
    System_SpriteScroll(scroll, EntityRegistry.get<TransformComponent>(player).source_rect);
    }
  auto players = EntityRegistry.view<SpriteScroll>();
  for(auto entity : players){
    const Uint8* state = SDL_GetKeyboardState(NULL);
    KeyHandle(state, EntityRegistry.get<TransformComponent>(entity));
    }



  //std::cout << player->health << std::endl;
  if(i % 600 == 0){
    //randomEnemySpawning();
  }

  SDL_RenderPresent(renderer);
}


void Game::randomEnemySpawning(){
  int x = rand() % Width;
  int y = rand() % Height;
  auto enemy = EntityRegistry.create();
  EntityRegistry.emplace<TransformComponent>(enemy,  x,y,0,0,32,32,x,y,128,128,TextureManager::load_texture("assets/sprites/wizard.png"),2);
  EntityRegistry.emplace<CharacterComponent>(enemy, true, false);
}

Game::~Game(){
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  TTF_Quit();
}
