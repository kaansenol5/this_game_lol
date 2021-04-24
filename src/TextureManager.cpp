#include "TextureManager.hpp"
#include "SDL_render.h"
#include <map>
#include <string>

std::map<std::string, SDL_Texture*> TextureManager::loaded_image_textures;