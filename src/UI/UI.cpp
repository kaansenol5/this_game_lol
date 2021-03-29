#include "UI.hpp"
#include "../TextureManager.hpp"
#include "colors.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

UI::UI(SDL_Renderer* renderer, const int& width, const int& height, int& current_scene_id)
: renderer(renderer), Width(width), Height(height), current_scene_id(current_scene_id) {
    Menu main_menu(width, height);
    main_menu.add_button("assets/fonts/font.ttf", "start", 24, Menu::CENTERED, [this](){
        change_scene(1);
    });
    main_menu.add_text("assets/fonts/font.ttf", "The Game", 128, Menu::TOP , Colors::Yellow);
    menus.push_back(main_menu);
}

void UI::render(){
    menus[current_menu].update();
    SDL_RenderPresent(renderer);
}

void UI::change_scene(int scene){
    current_scene_id = scene;
}


void UI::set_background_image(char *imgdir){
    background_image = TextureManager::load_texture(imgdir);
}

void UI::set_background_color(SDL_Color background_color){
    this->background_color = background_color;
}