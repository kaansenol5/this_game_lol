#include "SceneManager.hpp"
#include "SDL_events.h"
#include "SDL_image.h"
#include "SDL_keycode.h"
#include "SDL_ttf.h"
#include "UI/Button.hpp"
#include "UI/colors.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

unsigned short SceneManager::width = 0;
unsigned short SceneManager::height = 0;
SDL_Renderer* SceneManager::renderer =  nullptr;
bool SceneManager::is_running = false;

SceneManager::SceneManager(unsigned short width, unsigned short height){
    this->width = width;
    this->height = height;

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    start_scene = new UI(renderer, width, height);

    start_scene -> add_menu([this](Menu& menu){
        menu.add_text((char*) "assets/fonts/font.ttf", (char*) "Hello", 24, Menu::UP, Colors::White);
        menu.add_button((char*) "assets/fonts/font.ttf", (char*) "Start!", 36, Menu::CENTERED, true, [this](Button& button){
            current_scene = GAME;
        });
        menu.set_extra_event_handling([](SDL_Event event){
            switch (event.type) {
                case SDL_QUIT:
                    quit_game();
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit_game();
                            break;
                    }
            }
        });
    });
    game_scene = new Game;
    is_running = true;
}

SceneManager::~SceneManager(){
    delete start_scene;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void SceneManager::quit_game(){
    is_running = false;
}

bool SceneManager::check_running(){
    return is_running;
}

void SceneManager::update(){
    switch (current_scene) {
        case START_MENU:
            start_scene -> render();
            break;
        default:
            game_scene -> update_frame();
            break;
    }
}