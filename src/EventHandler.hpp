#pragma once
#include <SDL2/SDL_keyboard.h>
#include "GameObjectManager.hpp"
#include "JsonLoader.hpp"
#include "Keymap.h"

class EventHandler{
public:
    EventHandler();
    void handle_events();
private:
    Keymap keymap;
    Keymap load_keymap();
    json config;
    void on_key_down(SDL_Keysym sym);
    void on_mouse_click(int &x, int y);
};