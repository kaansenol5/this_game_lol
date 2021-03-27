#include <SDL2/SDL.h>
#include "JsonLoader.hpp"
#include "Game.hpp"
class EventHandler{
public:
  EventHandler(Game* game);
  void HandleEvents();
private:
  json config;
  Game* game;
  void PlayerController(const Uint8 *state);
  void OnKeyDown(SDL_Keycode sym);
};
