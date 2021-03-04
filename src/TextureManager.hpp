#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.hpp"

class TextureManager{
public:
  static inline SDL_Texture* load_texture(std::string dir){
    SDL_Surface* temp = IMG_Load(dir.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, temp);
    SDL_FreeSurface(temp);
    return texture;
  }
  static inline void render(SDL_Texture* texture, SDL_Rect source, SDL_Rect dest){
    if(dest.x > -100 && dest.x < Game::Width+100 && dest.y > -100 && dest.y < Game::Height+100){
      SDL_RenderCopy(Game::renderer, texture, &source, &dest);
    }
  }
};
