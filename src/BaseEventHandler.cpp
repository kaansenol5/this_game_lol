#include "BaseEventHandler.hpp"
#include "JsonLoader.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include "include/entt.hpp"
#include "SceneManager.hpp"
#include "GameObjectManager.hpp"
#include "EntityComponents/Player.hpp"




void BaseEventHandler::handle_events(){
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            SceneManager::quit_game();
            break;
        case SDL_KEYDOWN:
            on_key_down(event.key.keysym.sym);
            break;
    }
}