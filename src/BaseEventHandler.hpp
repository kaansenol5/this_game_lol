#pragma once
#include <SDL2/SDL_keyboard.h>
#include "SDL_keycode.h"
#include "JsonLoader.hpp"
#include "Keymap.h"
#include "SDL_events.h"

/* 
THIS IS A BASE CLASS FOR EVENT HANDLING
IT CALLS SDL_PollEvent()
SDL_PollEvent() or SDL_PumpEvents() SHOULD *NOT* BE CALLED ANYWHERE ELSE
*/

class BaseEventHandler{
public:
    void handle_events();
    SDL_Event event;
    virtual void on_key_down(SDL_Keycode keycode) = 0;
};