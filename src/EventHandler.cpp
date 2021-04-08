#include "EventHandler.hpp"
#include "JsonLoader.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include "include/entt.hpp"
#include "SceneManager.hpp"
#include "GameObjectManager.hpp"
#include "EntityComponents/Player.hpp"


EventHandler::EventHandler(){
    config = JsonLoader::load((char*)"config/keymap.json");
    keymap = load_keymap();
};

Keymap EventHandler::load_keymap(){
    return {config["left"], config["right"], config["up"], config["down"]};
}

void EventHandler::on_key_down(SDL_Keysym sym){
    switch (sym.sym) {
        case SDLK_ESCAPE:
            SceneManager::quit_game();
            break;
    }
}

void EventHandler::handle_events(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            SceneManager::quit_game();
            break;
        case SDL_KEYDOWN:
            on_key_down(event.key.keysym);
            break;
    }
    const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
    

    auto player_id = GameObjectManager::get_unique_entity_id<Player>();
    Player& player_component = GameObjectManager::EntityRegistry.get<Player>(player_id);
    player_component.handle_movement(keyboard_state, keymap);
}