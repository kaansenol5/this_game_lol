#pragma once
#include "SDL_rect.h"
#include "include/entt.hpp"
#include <vector>
#include <SDL2/SDL_render.h>
#include "JsonLoader.hpp"


class GameObjectManager{
public:
    GameObjectManager();
    ~GameObjectManager();
    void update_all();
    void render_all();
    void move_all(int x, int y);
    void spawn_player(int x, int y);
    void enemy_spawn_random();
    void landresource_spawn_random();
    void shoot_projectile(int subtag, SDL_Rect location, int x_direction, int y_direction, unsigned range = 4294967295);
    static entt::registry EntityRegistry;
    template<typename T>
    static inline entt::entity get_unique_entity_id(){ //hacky, yes. works, yes
        auto view = EntityRegistry.view<T>(); 
        if(view.size() > 1){
            std::cout << "WARNING: GameObjectManager::get_unique_entity_id(): Component is owned by multiple entities, this function is designed for unique entities which have specific components only they own (like the player and the Player class), by result, returned id is a random entity in list" << std::endl;
        }
        return view[0];
    }
    static entt::entity check_collision_with_any(SDL_Rect rect);
private:
    
    entt::entity spawn(int tag, int x, int y);
    std::vector<SDL_Texture*> textures;
    json config;
};