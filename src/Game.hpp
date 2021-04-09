#pragma once
#include "GameObjectManager.hpp"
#include "GameEventHandler.hpp"

class Game{
public:
    Game();
    void update_frame();
private:
    GameObjectManager objects_manager;
    GameEventHandler event_handler;
    void render();
    void update();
};