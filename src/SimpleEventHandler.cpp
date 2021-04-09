#include "SimpleEventHandler.hpp"
#include "SceneManager.hpp"

void SimpleEventHandler::on_key_down(SDL_Keycode keysym){
        switch (keysym) {
            case SDLK_ESCAPE:
                SceneManager::quit_game();
                break;
        }
    }