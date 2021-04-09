#pragma once
#include "GameObjectManager.hpp"


class Game{
public:
    Game();
    void update_frame();
private:
    GameObjectManager objects_manager;
    void render();
    void update();
};