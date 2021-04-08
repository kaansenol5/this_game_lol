#include "Player.hpp"
#include "../GameObjectManager.hpp"
#include "../SceneManager.hpp"
#include "TransformComponent.hpp"



void Player::handle_movement(const unsigned char *state, Keymap keymap){
    const auto id = entt::to_entity(GameObjectManager::EntityRegistry, *this);

    auto& transform_comp = GameObjectManager::EntityRegistry.get<TransformComponent>(id);
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