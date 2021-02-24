#include "Game.hpp"


class EventHandler{
public:
  void HandleEvents();
private:
  void HandleBaseEvents();
  void HandlePlayerEvents();
  SDL_Event event;
};
