#include "Entity.hpp"

Entity::Entity(char* texturesheet, SDL_Rect dstrect, int actual_width, int actual_height, int sprite_amount, int movement_speed, int damage)
: GameObject(texturesheet, dstrect, actual_width, actual_height, sprite_amount), movement_speed(movement_speed), damage(damage){

}

Entity::~Entity(){}
