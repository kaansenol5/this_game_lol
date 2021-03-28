#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "SceneManager.hpp"

class TextureManager{
public:
  static inline SDL_Texture* load_texture(std::string dir){
    SDL_Surface* temp = IMG_Load(dir.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(SceneManager::renderer, temp);
    SDL_FreeSurface(temp);
    return texture;
  }

  static inline SDL_Texture* load_ttf_font(char* font_dir, char* message, int ptsize, SDL_Color color){
    TTF_Font* font = TTF_OpenFont(font_dir, ptsize);
    SDL_Surface* temp_surface = TTF_RenderText_Solid(font, message, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(SceneManager::renderer, temp_surface);
    SDL_FreeSurface(temp_surface);
    TTF_CloseFont(font);
    return texture;

  }
  static inline void render(SDL_Texture* texture, SDL_Rect *source, SDL_Rect *dest){
    if(dest->x > -100 && dest->x < SceneManager::Width+100 && dest->y > -100 && dest->y < SceneManager::Height+100){ //check if destination rect is in the screen
      if(SDL_RenderCopy(SceneManager::renderer, texture, source, dest) != 0){
        std::cout << SDL_GetError() << dest->x << " "  << dest->y << std::endl;
      }
    }
  }
};
