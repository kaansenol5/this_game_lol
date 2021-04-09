#pragma once
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "UI/UI.hpp"
#include "Game.hpp"
#include "BaseEventHandler.hpp"

enum scene{
    START_MENU, GAME
};
class SceneManager{
public:
    SceneManager(unsigned short width, unsigned short height);
    ~SceneManager();
    void update();
    bool check_running();
    static void quit_game();
    static SDL_Renderer* renderer;
    static unsigned short width;
    static unsigned short height;
private:
    BaseEventHandler start_handler;
    UI* start_scene; 
    Game* game_scene;
    SDL_Window* window;
    static bool is_running;
    scene current_scene = START_MENU; 
};