#pragma once
#include <SDL2/SDL.h>
#include "JsonLoader.hpp"
#include "GameObjectManager.hpp"
#include "include/entt.hpp"
#include "Map.hpp"

class EventHandler{
public:
  EventHandler(GameObjectManager* objects_manager, entt::registry& EntityRegistry,  int screenwidth, int screenheight);
  void HandleEvents(Map* map);
private:
  entt::registry& EntityRegistry;
  json config;
  GameObjectManager* objects_manager;
  int screenwidth;
  int screenheight;
  void PlayerController(const Uint8 *state, Map* map);
  void OnKeyDown(SDL_Keycode sym);
};
