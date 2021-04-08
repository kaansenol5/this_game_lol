#pragma once
#include "../Keymap.h"


#define yes true

class Player{
public:
    void handle_movement(const unsigned char *state, Keymap Keymap);
private:
    bool entt_please_stop_pissing_me_of_ffs = yes; // entt does stupid shit when this aint here
};