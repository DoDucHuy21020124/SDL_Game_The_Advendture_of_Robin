#include "Game.h"
#include <time.h>
#include <windows.h>

Game* game = NULL;
bool is_played = false;

int main(int argc, char* argv[]) {
    srand(time(0));

    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint64 frameStart;
    int frameTime;

    do {

        if ( !is_played ) {
            game = new Game();
            game->game_init();
            is_played = true;
        }

        game->setup_game();

        play_music("music\\game_music.mp3");

        do {

            frameStart = SDL_GetTicks64();

            SDL_RenderClear(Game::renderer);

            game->update_game();
            game->render_game();
            game->handle_event();

            SDL_RenderPresent(Game::renderer);

            frameTime = SDL_GetTicks64() - frameStart;

            if ( frameDelay > frameTime ) {
                SDL_Delay(frameDelay - frameTime);
            }

        } while ( !game->get_game_over() );
    } while( game->get_is_running());

    game->clean_game();
    Sleep(3000);
    return 0;
}



