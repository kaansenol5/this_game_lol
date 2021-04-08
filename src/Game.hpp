#pragma once
#include "EventHandler.hpp"
#include "GameObjectManager.hpp"


class Game{
public:
    Game();
    void update_frame();
private:
    GameObjectManager objects_manager;
    EventHandler event_handler;
    void render();
    void update();
};