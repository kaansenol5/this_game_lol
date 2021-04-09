#include "Game.hpp"
#include "GameObjectManager.hpp"
#include "SDL_render.h"
#include "SceneManager.hpp"
#include "TextureManager.hpp"

Game::Game(){
    objects_manager.spawn_player(200, 200);
}

void Game::update(){
    objects_manager.update_all();
    event_handler.handle_events();
    event_handler.handle_player_movement();
}

void Game::render(){
    TextureManager::clear();
    objects_manager.render_all();
    SDL_RenderPresent(SceneManager::renderer);
}

void Game::update_frame(){
    update();
    render();
}