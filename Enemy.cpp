#include "Enemy.h"

Enemy::Enemy(const char* filePath, Vector2D position, int numFrame, Vector2D vel) : TextureManager(filePath, position, numFrame) {
    velocity = vel;
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

