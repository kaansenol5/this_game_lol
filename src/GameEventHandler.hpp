#pragma once
#include "BaseEventHandler.hpp"

class GameEventHandler : public BaseEventHandler{
public:
    GameEventHandler();
    void handle_player_movement();
    void load_keymap();
private:
    json config;
    Keymap keymap;
};