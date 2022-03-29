#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"

const int BACKGROUND_WIDTH = 1200;
const int BACKGROUND_HEIGHT = 800;

class Map : public TextureManager {
public :
    Map(const char* filePath, Vector2D pos, int numFrame, int speed);
    ~Map();

    void set_xpos(const int& xpos) {destRect.x = xpos;}
    void set_ypos(const int& ypos) {destRect.y = ypos;}
    void set_xypos(Vector2D position) {destRect.x = int(position.x); destRect.y = int(position.y);}

    void handle_move();
    void check_limit_map();
    void update();
};

#endif // MAP_H

