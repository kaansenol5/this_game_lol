#pragma once
#include "SDL_render.h"

class TextureComponent{
public:
    TextureComponent(SDL_Texture* texture, unsigned x_animation_count, unsigned y_animation_count, int width, int height);
    void render();
private:
    SDL_Texture* texture;
    SDL_Rect source_rect;
    void animate();
    unsigned x_animation_count;
    unsigned y_animation_count;
};