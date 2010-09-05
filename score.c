#include "score.h"


void draw_score(game_t* game, screen_t* screen, int x, int y)
{
    char score[20];
    sprintf(score, "%d", game->score.score);
    draw_text(score, x, y, screen);
}

void draw_level(game_t* game, screen_t* screen, int x, int y)
{
    char level[20];
    sprintf(level, "%d", game->score.level);
    draw_text(level, x, y, screen);    
}
