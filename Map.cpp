#include "Map.h"
#include "Game.h"

Map::Map(const char* filePath, Vector2D position, int numFrame) : TextureManager(filePath, position, numFrame) {

}

Map::~Map() {

}

void Map::handle_move() {
    destRect.x -= 10;
}

void Map::check_limit_map() {
    if ( destRect.x <= -(BACKGROUND_WIDTH) ) destRect.x = SCREEN_WIDTH;
}

void Map::update() {
    handle_move();
    check_limit_map();
}


