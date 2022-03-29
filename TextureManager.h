#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>
#include <string>
#include "Vector2D.h"

class TextureManager {
protected :
    const char* file_path;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    int frame;
    int speed;
    int num_frame;

public :
    TextureManager(const char* filePath, Vector2D position, int numFrame);
    ~TextureManager();

    void set_file_path(const char* filePath, int numFrame);

    int get_xpos() const {return destRect.x;}
    void set_xpos(const int& xpos) {destRect.x = xpos;}
    int get_ypos() const {return destRect.y;}
    void set_ypos(const int& ypos) {destRect.y = ypos;}
    void set_xypos(const Vector2D& position) {destRect.x = int(position.x); destRect.y = int(position.y);}

    SDL_Rect get_destRect() const {return destRect;}

    void draw(const SDL_RendererFlip render_flip = SDL_FLIP_NONE, const double angle = 0, const SDL_Point* center = NULL);
};

#endif // TEXTURE_MANAGER_H
