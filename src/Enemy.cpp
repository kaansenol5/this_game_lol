#include "Game.hpp"

Enemy::Enemy(char* texturesheet, SDL_Rect dstrect, int actual_width, int actual_height, int sprite_amount, int movement_speed, int damage)
: Entity(texturesheet, dstrect, actual_width, actual_height, sprite_amount, movement_speed, damage){

}

Enemy::~Enemy(){};

void Enemy::AttackPlayer(){
  if(destination_rect.x >= Game::player->destination_rect.x - (actual_width+Game::player->actual_width) && destination_rect.x <= Game::player->destination_rect.x + (actual_width+Game::player->actual_width) && destination_rect.y >= Game::player->destination_rect.y - (actual_width+Game::player->actual_width) && destination_rect.y <= Game::player->destination_rect.y + (actual_width+Game::player->actual_width)){
    HitPlayer();
  }
  else{
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
