#include <SDL2/SDL.h>

class Projectile{
public:
  Projectile();
  ~Projectile();
private:
  SDL_Texture* texture;
  int end_destination_x; // Where the projectile is shooted at
  int end_destination_y; // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
};
