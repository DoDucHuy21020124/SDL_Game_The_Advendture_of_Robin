#include "Game.h"
#include <time.h>
#include <windows.h>

Game* game = NULL;
bool is_played = false;
bool play_again = false;

int main(int argc, char* argv[]) {
    srand(time(0));

    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint64 frameStart;
    int frameTime;
    int click;

    do {

        if ( !is_played ) {
            game = new Game();
            game->game_init();
            is_played = true;

        }

        if ( !play_again ) {
            if ( !Mix_PlayingMusic() ) play_music("music\\menu_music.mp3");
            click = game->make_menu();
        }

        if ( click == 3 ) break;
        else if ( click == 1 ) game->make_high_score();
        else if ( click == 2 ) game->make_info_game();
        else if ( click == 0 ) {

            game->set_game_over(false);
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

            play_music("music\\menu_music.mp3");
            if ( game->make_play_again() == 0 ) {
                click = 0;
                play_again = true;
            }
            else {
                play_again = false;
            }
        }
    } while( game->get_is_running() );

    game->clean_game();
    Sleep(3000);
    return 0;
}



