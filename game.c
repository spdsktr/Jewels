#include "game.h"
#include "board.h"
#include <stdio.h>

void new_game(game_t* game)
{
    game->delay=0;
                                        
    create_board(&(game->board));
    
    update_board(game, NULL);
        
    game->delay = GFX_DELAY;
    game->score.score = 0;
    game->score.level = 1;
    game->bonus.last = 0;
    game->bonus.next = 2000;

}

int load_game(game_t* game)
{
    FILE* saved_game;
    
    saved_game = fopen(".gemzsave", "r");
    if (saved_game)
    {
        fread(game, sizeof(game_t), 1, saved_game);
        fclose(saved_game);
        return 1;
    }
    return 0;
}

void save_game(game_t* game)
{
    FILE* saved_game;
    
    saved_game = fopen(".gemzsave", "w");
    if (saved_game)
    {
        fwrite(game, sizeof(game_t), 1, saved_game);
	fclose(saved_game);
    }
}
