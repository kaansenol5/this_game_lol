#pragma once
#include <SDL2/SDL.h>
#include "JsonLoader.hpp"
#include "GameObjectManager.hpp"
#include "include/entt.hpp"
#include "Map.hpp"



struct Keymap{
  int left, right , up, down;
};



class EventHandler{
public:
  EventHandler(GameObjectManager* objects_manager, entt::registry& EntityRegistry,  int screenwidth, int screenheight, bool& game_running);
  void HandleEvents(Map* map);
private:
  Keymap keymap;
  entt::registry& EntityRegistry;
  json config;
  bool& game_running;
  GameObjectManager* objects_manager;
  int screenwidth;
  int screenheight;
  void PlayerController(const Uint8 *state, Map* map);
  void OnKeyDown(SDL_Keycode sym);
};
