#pragma once
#include "BaseEventHandler.hpp"
#include "SDL_keycode.h"

class SimpleEventHandler : public BaseEventHandler
{
public:
    virtual void on_key_down(SDL_Keycode keysym);
};