#pragma once
#include "EntityComponents/Transform.hpp"
#include "EntityComponents/NPC.hpp"
#include "JsonLoader.hpp"
#include "include/entt.hpp"
#include <vector>


class GameObjectManager{
public:
  GameObjectManager(int width, int height);
  ~GameObjectManager();
  void update(int width, int height);
  void render_all();
  void move_all(int x, int y);
  void enemy_spawn_random(int width, int height);
  void spawn(int tag, int x, int y);
  void landresource_spawn_random(int mapsize, int tilesize);
  entt::registry EntityRegistry;
private:
  int width;
  int height;
  json config;
  std::vector<SDL_Texture*> textures;
};
