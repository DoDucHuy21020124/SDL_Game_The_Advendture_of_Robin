#ifndef GAME_H
#define GAME_H

#include "GeneralFunction.h"
#include "Map.h"
#include "Character.h"
#include "Enemy.h"

class Game {
private :
    SDL_Window* window;
    bool is_running = true;
    bool game_over = false;

public :
    static SDL_Renderer* renderer;
    static SDL_Texture* background;
    static Map* map_game1;
    static Map* map_game2;
    static SDL_Event g_event;
    static Character* character;
    static Enemy* enemy;
    static Enemy* dragon;
    static Enemy* bat;

    bool get_is_running() const {return is_running;}
    bool get_game_over() const {return game_over;}
    void set_is_running(const bool& running) {is_running = running;}
    void set_game_over(const bool& over) {game_over = over;}


    void game_init();
    void setup_game();
    void handle_event();
    void update_game();
    void render_game();
    void clean_game();
};

#endif // GAME_H

