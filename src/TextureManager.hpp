#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "SDL_error.h"
#include "SceneManager.hpp"

/* 
ALL OF THE FUNCTIONS ASSUMES THAT SDL_Init(), TTF_Init() and IMG_Init were called earlier
*/

class TextureManager{
public:
    static inline SDL_Texture* load_image(const char* file){
        SDL_Surface* temp_surface = IMG_Load(file);
        if(!temp_surface){
            std::cout << "IMG_Load(" << file << ") call has returned nullptr. Error Code: "  << IMG_GetError() << std::endl;
         }      
        SDL_Texture* texture = SDL_CreateTextureFromSurface(SceneManager::renderer, temp_surface);
        if (!texture){
            std::cout << "Texture loaded by TextureManager::load_image() may be invalid, image file name: " << file << std::endl;
            std::cout << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(temp_surface);
        return texture;
    }

    static inline SDL_Texture* load_ttf_font(const char* font_file, const char* text, const int ptsize, const SDL_Color color){
        TTF_Font* loaded_font = TTF_OpenFont(font_file, ptsize);
        if(!loaded_font){
            std::cout << "Failed loading font by TextureManager::load_ttf_font() , font file name: " << font_file << std::endl;
            std::cout << "Error Code: " << TTF_GetError() << std::endl;
        }
        SDL_Surface* temp_surface = TTF_RenderText_Solid(loaded_font, text, color);
        if(!temp_surface){
            std::cout << "TTF_RenderText_Solid() failed, Error Code: " << SDL_GetError() << std::endl;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(SceneManager::renderer, temp_surface);        
        if (!texture){
            std::cout << "Texture generation failed at TextureManager::load_ttf_font() " << font_file << std::endl;
            std::cout << "Error Code: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(temp_surface);
        TTF_CloseFont(loaded_font);
        return texture;
    }

    static inline bool check_bounds(SDL_Rect* dest){
        if(dest->x > 0 && dest->x < SceneManager::width && dest->y > 0 && dest->y < SceneManager::height){
            return true;
        }
        else{
            return false;
        }
    }

    static inline void render(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* dest){
        if(check_bounds(dest)){ //check if destination rect is in the screen
            if(SDL_RenderCopy(SceneManager::renderer, texture, source, dest) != 0){
                std::cout << "Failed rendering!!: " << SDL_GetError() << " at x:" <<  dest->x << ", y: "  << dest->y << std::endl;
              //  std::cout << "Texture: " << texture << std::endl;
            }
        }
    }

    static inline void draw_rect(SDL_Rect *dest, bool filled, SDL_Color color){
        if(check_bounds(dest)){
            SDL_SetRenderDrawColor(SceneManager::renderer, color.r, color.g, color.b, color.a);
            if(filled){
                if(SDL_RenderFillRect(SceneManager::renderer, dest) != 0){
                    std::cout << "SDL_RenderFillRect() failed! Error Code: " << SDL_GetError() << std::endl;
                };
            }
            else{
                if(SDL_RenderDrawRect(SceneManager::renderer, dest) != 0){
                    std::cout << "SDL_DrawRect() failed! Error Code: " << SDL_GetError() << std::endl;
                }
            }
            SDL_SetRenderDrawColor(SceneManager::renderer, 0, 0, 0, 0);
        }
  }

  static inline void clear(unsigned char r = 0, unsigned char b = 0, unsigned char g = 0, unsigned char a = 255){
      SDL_SetRenderDrawColor(SceneManager::renderer, r, g, b, a);
      SDL_RenderClear(SceneManager::renderer);
  }
};