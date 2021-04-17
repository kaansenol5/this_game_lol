#pragma once
#include "BaseEventHandler.hpp"
#include "GameObjectManager.hpp"
#include "SDL_keycode.h"

class GameEventHandler : public BaseEventHandler{
public:
    GameEventHandler(GameObjectManager& objects_manager);
    void handle_player_movement();
    void load_keymap();
    void handle_mouse();
    virtual void on_key_down(SDL_Keycode keycode);
private:
    int frame_counter = 0;
    GameObjectManager& objects_manager;
    json config;
    Keymap keymap;
};