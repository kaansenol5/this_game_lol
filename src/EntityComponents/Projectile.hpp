#pragma once

#include "SDL_rect.h"
#include "TransformComponent.hpp"

class Projectile{
public:
    Projectile(SDL_Rect start_loc, int target_x, int target_y, unsigned range);
    void update();
private:
    SDL_Rect start_loc;
    unsigned range;
    int target_x;
    int target_y;
    int x_direction;
    int y_direction;
    double m;
    bool y_move;
    unsigned moved_for_frames = 0;
};