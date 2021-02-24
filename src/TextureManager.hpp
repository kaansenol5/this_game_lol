#pragma once
#include "Game.hpp"

class TextureManager{
  TextureManager() = delete;
public:
  static SDL_Texture* load_texture(const char* file_name);
};
