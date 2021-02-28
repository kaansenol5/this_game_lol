#include "Game.hpp"
//do not be suspicious of this, it is simple, it works, you wrote the file_name wrong if you think this doesn't work.
//dont touch
SDL_Texture* TextureManager::load_texture(const char *file_name){
  SDL_Surface* temp_surface = IMG_Load(file_name);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, temp_surface);
  SDL_FreeSurface(temp_surface);
  return texture;
}
