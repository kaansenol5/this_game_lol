#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.hpp"

class TextureManager{
public:
  static inline SDL_Texture* load_texture(char* dir){
    SDL_Surface* temp = IMG_Load(dir);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, temp);
    SDL_FreeSurface(temp);
    return texture;
  }
  static inline void render(SDL_Texture* texture, SDL_Rect source, SDL_Rect dest){
    SDL_RenderCopy(Game::renderer, texture, &source, &dest);
  }
};
