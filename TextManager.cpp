#include "TextManager.h"
#include "Game.h"

TextManager::TextManager() {
    text = "";
    text_color = {0, 0, 0};
    file_path = "font\\FVF Fernando 08.ttf";

    font_size = 30;
    font = TTF_OpenFont(file_path, font_size);

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
    texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);

    TTF_SizeText(font, text.c_str(), &srcRect.w, &srcRect.h);
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = 500;
    destRect.y = 2;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

TextManager::TextManager(std::string text_, SDL_Color text_color_, const char* filePath, int fontSize, Vector2D position) : text(text_), text_color(text_color_), file_path(filePath), font_size(fontSize) {
    font = TTF_OpenFont(file_path, font_size);

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
    texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);

    TTF_SizeText(font, text.c_str(), &srcRect.w, &srcRect.h);
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = int(position.x);
    destRect.y = int(position.y);
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

TextManager::~TextManager() {

}

void TextManager::update() {
    font = TTF_OpenFont(file_path, font_size);

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
    texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);

    TTF_SizeText(font, text.c_str(), &srcRect.w, &srcRect.h);
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

void TextManager::draw() {
    SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}


