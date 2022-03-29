#include "Weapon.h"

Weapon::Weapon(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel) : TextureManager(filePath, position, numFrame, speed) {
    velocity = vel;
    is_move = true;
}

Weapon::~Weapon() {

}

void Weapon::handle_move() {
    destRect.x += int(velocity.x);
    destRect.y += int(velocity.y);
}

void Weapon::update() {
    handle_move();
    TextureManager::update();
}
