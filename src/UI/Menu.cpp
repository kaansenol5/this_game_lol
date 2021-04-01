#include "Menu.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>

Menu::Menu(const int& Width, const int& Height)
: Width(Width), Height(Height){

}




void Menu::update(){
    for(auto button : buttons){
        button.render();
    }
    for(auto text : texts){
        text.render();
    }
    handle_events();
}

void Menu::set_xy(item_location location, int& x, int& y){
    switch (location) {
        case CENTERED:
            x = (Width/2) - default_item_width;
            y = (Height/2) - default_item_height;
            break;
        case LEFT:
            x = 15;
            y = default_side_item_padding;
            break;
        case RIGHT:
            x = Width - 15 - default_item_width;
            y = default_side_item_padding;
            break;
        case DOWN:
            x = default_side_item_padding;
            y = 15;
            break;
        case BOTTOM:
            x = default_side_item_padding;
            y = Height - 15 - default_item_height;
            break;
        case TOP:
            x = Width / 2 - default_item_width;
            y = 15;
            break;
    }

    for(auto button : buttons){
        if(button.location.y == y){
                y += default_item_height;
            }
        }
    for(auto text : texts){
        if(text.location.y == y){
             y += default_item_height;
        }
    }
}

void Menu::add_button(char* fontdir, char* text, int ptsize, item_location location,  const std::function<void()> fn){
    SDL_Rect dst_rect;
    int x, y;
    set_xy(location, x, y);
    dst_rect = {x, y, default_item_width, default_item_height};
    buttons.push_back((Button){fontdir, text, ptsize, dst_rect, fn});
}

void Menu::add_text(char* fontdir, char* text, int ptsize, item_location location,  SDL_Color color){
    SDL_Rect dst_rect;
    int x, y;
    set_xy(location, x, y);
    dst_rect = {x, y, default_item_width, default_item_height};
    texts.push_back({fontdir, text, ptsize, color, dst_rect});
}

void Menu::handle_events(){
    SDL_PumpEvents();
    int x, y;
    Uint32 mouse_state = SDL_GetMouseState(&x, &y);
    for(auto& button : buttons){
        if(x > button.location.x && x < button.location.x + button.location.w && y > button.location.y && y < button.location.y + button.location.h){
            button.selected = true;
            if(mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)){
                button.on_click(); 
            }
        }
        else {
            button.selected = false;
        }
        
    }
}
