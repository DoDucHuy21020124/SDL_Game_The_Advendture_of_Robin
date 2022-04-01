#include "Enemy.h"

Enemy::Enemy(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel) : TextureManager(filePath, position, numFrame, speed) {
    velocity = vel;
    hp = 0;
    score = 0;
    is_destroyed = false;
    is_destroying = false;
}

Enemy::~Enemy() {

}

void Enemy::handle_move() {
    destRect.x += int(velocity.x);
    destRect.y += int(velocity.y);
}

void Enemy::update() {
    handle_move();
    TextureManager::update();
}

