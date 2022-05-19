#include "GeneralFunction.h"

Mix_Chunk* sound_effect = NULL;
Mix_Music* music_game = NULL;

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
    return false;
}

void play_music(const char* file_path) {
    if ( Mix_PlayingMusic() ) Mix_HaltMusic();
    music_game = Mix_LoadMUS(file_path);
    Mix_PlayMusic(music_game, -1);
}

void play_sound_effect(const char* file_path) {
    sound_effect = Mix_LoadWAV(file_path);
    Mix_PlayChannel(-1, sound_effect, 0);
}

bool check_in_button(const int& x, const int& y, const SDL_Rect& rect) {
    if ( x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h ) return true;
    return false;
}
