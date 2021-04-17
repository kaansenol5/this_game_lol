#pragma once
#include "../TextureManager.hpp"
#include <SDL2/SDL_render.h>

class TransformComponent{
public:
    TransformComponent(int x, int y, int w, int h, int real_w, int real_h, bool is_animated, int x_animation_count, int y_animation_count, SDL_Texture* texture, int speed);
    void render();
    void move(int x_diff, int y_diff, bool with_speed = true);
    void set_xy(int x, int y);
    SDL_Rect destination_rect;
    int base_speed;
private:
    void animate();
    int current_speed = base_speed;
    int real_width;
    int real_height;
    int width;
    int height;
    SDL_Rect source_rect;
    bool is_animated;
    int x_animation_count;
    int y_animation_count;
    bool y_animate;
    bool x_animate;
    int current_sprite_x;
    int current_sprite_y;
    SDL_Texture* texture;
};