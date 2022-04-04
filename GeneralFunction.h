#ifndef GENERAL_FUNCTION_H
#define GENERAL_FUNCTION_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int GROUND_HEIGHT = 550;

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file_path);
bool check_collision(const SDL_Rect& rect1, const SDL_Rect& rect2);
void play_music(const char* file_path);
void play_sound_effect(const char* file_path);
bool check_in_button(const int& x, const int& y, const SDL_Rect& rect);

#endif // GENERAL_FUNCTION_H
