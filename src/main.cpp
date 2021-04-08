#include "JsonLoader.hpp"
#include "SceneManager.hpp"
#include <SDL2/SDL_timer.h>
#include <iostream>

int main(int argc, char* argv[]){
    json config = JsonLoader::load((char*)"config/game_config.json");
    const unsigned char FPS = config["FPS"];
    const int frame_delay = 1000 / FPS;
    unsigned long frame_start;
    int frame_time;
    unsigned long long frame_counter = 0;

    SceneManager scene_manager(config["width"], config["height"]);

    while (scene_manager.check_running()){
        frame_start = SDL_GetTicks();
        scene_manager.update();
        frame_counter++;

        frame_time = SDL_GetTicks() - frame_start;
        if(frame_delay > frame_time){
            SDL_Delay(frame_delay - frame_time);
        }
    }

    std::cout << "bye!" << std::endl;
}