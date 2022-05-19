#include "TextureManager.h"
#include "GeneralFunction.h"
#include "Game.h"

TextureManager::TextureManager(const char* filePath, Vector2D position, int numFrame, int speed_) {
    file_path = filePath;
    frame = 0;
    num_frame = numFrame;
    speed = speed_;
    texture = load_texture(Game::renderer, file_path);
    SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);
    srcRect.w = srcRect.w/num_frame;
    srcRect.x = frame * srcRect.w;
    srcRect.y = 0;

    destRect.x = int(position.x);
    destRect.y = int(position.y);
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;

}

TextureManager::~TextureManager() {
    if ( texture != NULL ) {
        delete texture;
        texture = NULL;
    }
}

void TextureManager::set_file_path(const char* filePath, int numFrame) {
    file_path = filePath;
    num_frame = numFrame;
    frame = 0;
    texture = load_texture(Game::renderer, file_path);
    SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);
    srcRect.w = srcRect.w/num_frame;
    srcRect.x = frame * srcRect.w;
    srcRect.y = 0;
    destRect.w = srcRect.w;
}

void TextureManager::update() {
    frame = (SDL_GetTicks64()/speed)%num_frame;
    srcRect.x = frame * srcRect.w;
}

void TextureManager::draw(SDL_RendererFlip render_flip, const double angle, const SDL_Point* center) {
    SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &destRect, angle, center, render_flip);
}


