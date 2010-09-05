#include <unistd.h>

#include "bonus.h"
#include "board.h"

void draw_screen(game_t* game, screen_t* screen);

void apply_bonus(game_t* game, screen_t* screen)
{
    if(screen)
  	{  	  	
	    game->bonus.last = game->bonus.next;
	    game->bonus.next = game->bonus.next+game->bonus.next*2;	
	    (game->score.level)++;
	    //draw_text("** BONUS **", 160, SCREEN_HEIGHT/2-50, screen);  
	    draw_canvas(screen->bonusOverlay, screen, 0, 0);
	    SDL_Flip(screen->screen);
	    usleep(2500000);
	    remove_bonus(game);
	    draw_screen(game, screen);
	    usleep(GFX_DELAY);
	    apply_gravity(&(game->board));
	    refill_board(&(game->board));
	    update_board(game, screen);
  	}
}

void draw_bonus(game_t* game, screen_t* screen, int x, int y)
{
    rect_t rect;
    rect_t src_rect;
    double per = 1 - (double)(game->score.score - game->bonus.last)/(game->bonus.next - game->bonus.last);
    
    rect.x = x;
    rect.y = y;
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = screen->bonus->w;
    src_rect.h = screen->bonus->h * per;
    
    SDL_BlitSurface(screen->bonus, &src_rect, screen->screen, &rect);
}
