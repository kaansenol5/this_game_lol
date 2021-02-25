#include "Game.hpp"

Enemy::Enemy(char* texturesheet, SDL_Rect dstrect, int actual_width, int actual_height, int sprite_amount, int movement_speed, int damage)
: GameObject(texturesheet, dstrect, actual_width, actual_height, sprite_amount), movement_speed(movement_speed), damage(damage){

}

Enemy::~Enemy(){};

void Enemy::AttackPlayer(){
  if(destination_rect.x < Game::player->destination_rect.x){
    destination_rect.x += movement_speed;
  }
  if(destination_rect.x > Game::player->destination_rect.x){
    destination_rect.x -= movement_speed;
  }
  if(destination_rect.y < Game::player->destination_rect.y){
    destination_rect.y += movement_speed;
  }
  if(destination_rect.y > Game::player->destination_rect.y){
    destination_rect.y -= movement_speed;
  }
  if(destination_rect.x == Game::player->destination_rect.x && destination_rect.y == Game::player->destination_rect.y){
    HitPlayer();
  }
}




void Enemy::HitPlayer(){
  attacking=true;
  Game::player->health -= damage;
}

void Enemy::update(){
  GameObject::update();
  AttackPlayer();
}
