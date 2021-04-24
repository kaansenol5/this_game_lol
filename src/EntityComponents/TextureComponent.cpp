#include "TextureComponent.hpp"
#include "../GameObjectManager.hpp"
#include "../include/entt.hpp"
#include "TransformComponent.hpp"
#include "../TextureManager.hpp"

TextureComponent::TextureComponent(SDL_Texture* texture, unsigned x_animation_count, unsigned y_animation_count, int width, int height)
: texture(texture), x_animation_count(x_animation_count), y_animation_count(y_animation_count) {
    source_rect = {0, 0, width, height};
}

void TextureComponent::animate(){
    unsigned current_animation_x_frame = source_rect.x / source_rect.w;
    unsigned current_animation_y_frame = source_rect.y / source_rect.h;
    if(current_animation_x_frame < x_animation_count){
        source_rect.x += source_rect.w;
    }
    else {
        source_rect.x = 0;
    }
    if(current_animation_y_frame < y_animation_count){
        source_rect.y += source_rect.h;
    }
    else {
        source_rect.y = 0;
    }
}

void TextureComponent::render(){
    animate();
    entt::entity this_entity = entt::to_entity(GameObjectManager::EntityRegistry, *this);
    SDL_Rect destination_rect = GameObjectManager::EntityRegistry.get<TransformComponent>(this_entity).destination_rect;
    TextureManager::render(texture, &source_rect, &destination_rect); // destination_rect was a pointer, so no &
}