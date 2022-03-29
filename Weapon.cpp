#include "Weapon.h"

Weapon::Weapon(const char* filePath, Vector2D position, int numFrame, Vector2D vel) : TextureManager(filePath, position, numFrame) {
    velocity = vel;
}

Weapon::~Weapon() {

}

void Weapon::handle_move() {
    destRect.x += int(velocity.x);
    destRect.y += int(velocity.y);
}

void Weapon::update() {
    handle_move();
}
