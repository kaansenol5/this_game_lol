#include "GameEventHandler.hpp"
#include "GameObjectManager.hpp"
#include "JsonLoader.hpp"
#include "SDL_keyboard.h"
#include "EntityComponents/Player.hpp"
#include "EntityComponents/TransformComponent.hpp"
#include "SDL_keycode.h"
#include "SDL_mouse.h"
#include "SDL_scancode.h"
#include "SceneManager.hpp"

GameEventHandler::GameEventHandler(GameObjectManager& objects_manager):objects_manager(objects_manager){
    load_keymap();


}

void GameEventHandler::load_keymap(){
    config = JsonLoader::load("config/keymap.json");
    keymap = {config["left"],config["right"],config["up"],config["down"]};
}


void GameEventHandler::handle_player_movement(){
    const Uint8* state = SDL_GetKeyboardState(0);
    auto player_id = GameObjectManager::get_unique_entity_id<Player>();
    auto& transform_comp = GameObjectManager::EntityRegistry.get<TransformComponent>(player_id);
    SDL_Rect& location = transform_comp.destination_rect;

    if (state[keymap.up]){
        if (location.y > 200){
            transform_comp.move(0, -1);
        }
        else {
            // do map thing here
        }
    }

    if (state[keymap.down]){
        if (location.y < SceneManager::height - 200){
            transform_comp.move(0, 1);
        }
        else {

        }
    }

    if (state[keymap.left]){
        if (location.x > 200){
            transform_comp.move(-1, 0);
        }
        else {

        }
    }

    if (state[keymap.right]){
        if (location.x < SceneManager::width - 200){
            transform_comp.move(1, 0);
        }
        else{

        }
    }
}

void GameEventHandler::handle_mouse(){
    int x, y;
    frame_counter++;
    Uint32 mouse_state = SDL_GetMouseState(&x, &y);
    if((mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))){
        auto player_id = GameObjectManager::get_unique_entity_id<Player>();
        auto& transform_comp = GameObjectManager::EntityRegistry.get<TransformComponent>(player_id);
        SDL_Rect& location = transform_comp.destination_rect;
        objects_manager.shoot_projectile(0, location, x, y, 600);
    }
}


void GameEventHandler::on_key_down(SDL_Keycode keycode){
    switch (keycode) {
    }
}

