#include "Bat.h"

Bat::Bat(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel) : Enemy(filePath, position, numFrame, speed, vel) {
    hp = 2;
}

Bat::~Bat() {

}
