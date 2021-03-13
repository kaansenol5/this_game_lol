#pragma once
#include "EntityComponents/Transform.hpp"
#include "EntityComponents/NPC.hpp"
#include "JsonLoader.hpp"
#include <vector>


class GameObjectManager{
public:
  GameObjectManager();
  void update();
  void render_all();
  void move_all(int x, int y);
  void enemy_spawn_random();
  void spawn(int tag, int x, int y);
  void landresource_spawn_random(int mapsize, int tilesize);
private:
  json config;
  std::vector<SDL_Texture*> textures;
};
