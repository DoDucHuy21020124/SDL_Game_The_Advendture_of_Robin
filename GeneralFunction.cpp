#include "GeneralFunction.h"

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file_path) {
    SDL_Surface* surface = IMG_Load(file_path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

bool check_collision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
    if ( rect1.x + rect1.w >= rect2.x &&
        rect1.y + rect1.h >= rect2.y &&
        rect2.x + rect2.w >= rect1.x &&
        rect2.y + rect2.h >= rect1.y ) return true;
}
