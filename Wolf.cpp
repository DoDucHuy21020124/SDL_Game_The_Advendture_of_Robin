#include "Wolf.h"

Wolf::Wolf(const char* filePath, Vector2D position, int numFrame, int speed, Vector2D vel) : Enemy(filePath, position, numFrame, speed, vel) {
    hp = 5;
}

Wolf::~Wolf() {

}
