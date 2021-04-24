#pragma once
#include "SDL_pixels.h"
#include <SDL2/SDL_rect.h>

class TransformComponent{
public:
    TransformComponent(int x, int y, int w, int h, bool filled = false);
    SDL_Rect destination_rect;
    void render();
    void move(int xd, int yd);
private:
    bool filled;
    SDL_Color color;
};