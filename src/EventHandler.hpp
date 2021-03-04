#include <SDL2/SDL.h>
#include "JsonLoader.hpp"

class EventHandler{
public:
  EventHandler();
  void HandleEvents();
private:
  json config;
  void PlayerController(const Uint8 *state);
  void OnKeyDown(SDL_Keycode sym);
};
