#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "board.h"
#include "bonus.h"
#include "SDL_mixer.h"

int part_of_move(board_t* board, int x, int y);
int check_board(board_t* board, int x, int y, int type);
int check_moves(board_t* board, int x, int y);
void draw_screen(game_t* game, screen_t* screen);
void swap_pieces(board_t* board, int x1, int y1, int x2, int y2);

extern Mix_Chunk *SFX_JewelDrop;
extern Mix_Chunk *SFX_JewelGravity;

void create_board(board_t* board)
{
    int x, y;
    
    srand(time(NULL));

    for (y = 0; y<BOARD_HEIGHT; y++)
    {
        for (x = 0; x<BOARD_WIDTH; x++)
        {
            board->data[x][y] = rand() % JEWEL_COUNT;
        }
    }

    board->sel_x = -1;
    board->sel_y = -1;
}

void update_board(game_t* game, screen_t* screen)
{		
    int counter = 1;
    
    while(remove_matches(game, screen, counter))
    {        
        apply_gravity(&(game->board));
        refill_board(&(game->board));   
        
        if (game->score.score >= game->bonus.next)
        {
            draw_screen(game, screen);
            apply_bonus(game, screen);
        }
        counter++;
    }

    save_game(game);
    
}

int remove_matches(game_t* game, screen_t* screen, int mult)
{
    int x, y;
    int ret = 0;
    int x_removes[64];
    int y_removes[64];
    int counter = 0;

    for (y = 0; y<BOARD_HEIGHT; y++)
    {
        for (x = 0; x<BOARD_WIDTH; x++)
        {
            if(check_moves(&(game->board), x, y))
            {
                x_removes[counter] = x;
                y_removes[counter] = y;
                counter++;
                ret = 1;
            }
        }
    }

    if (counter)
    {
        Mix_PlayChannel( -1, SFX_JewelDrop, 0 );
        draw_screen(game, screen);
        usleep(game->delay);
        game->score.score += counter * mult * POINTS_PER_PIECE * game->score.level;
        for (x = 0; x < counter; x++)
        {
            game->board.data[x_removes[x]][y_removes[x]] = -1;
        }
        draw_screen(game, screen);
        usleep(game->delay);
    }
    return ret;
}

int check_moves(board_t* board, int x, int y)
{
    if ((check_board(board, x-2, y, board->data[x][y]) &&
         check_board(board, x-1, y, board->data[x][y]))
        ||
        (check_board(board, x-1, y, board->data[x][y]) &&
         check_board(board, x+1, y, board->data[x][y]))
        ||
        (check_board(board, x+1, y, board->data[x][y]) &&
         check_board(board, x+2, y, board->data[x][y]))
        ||
        (check_board(board, x, y-2, board->data[x][y]) &&
         check_board(board, x, y-1, board->data[x][y]))
        ||
        (check_board(board, x, y-1, board->data[x][y]) &&
         check_board(board, x, y+1, board->data[x][y]))
        ||
        (check_board(board, x, y+1, board->data[x][y]) &&
         check_board(board, x, y+2, board->data[x][y])))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void apply_gravity(board_t* board)
{
    int x,y;
    int i;
    
    Mix_PlayChannel( -1, SFX_JewelGravity, 0 );
    
    for (i = 0; i<BOARD_HEIGHT-1; i++)
    {
        for (y = 0; y<BOARD_HEIGHT-1; y++)
        {
            for (x = 0; x<BOARD_WIDTH; x++)
            {
                if (board->data[x][y+1] == -1)
                {
                    board->data[x][y+1] = board->data[x][y];
                    board->data[x][y] = -1;
                }
            }
        }    
    }
}

void refill_board(board_t* board)
{
    int x, y;

    for (y = 0; y < BOARD_HEIGHT; y++)
    {
        for (x = 0; x < BOARD_WIDTH; x++)
        {
            if (board->data[x][y] == -1)
            {
                board->data[x][y] = rand() % JEWEL_COUNT;
            }
        }
    }    
}

int check_board(board_t* board, int x, int y, int type)
{
    if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT)
    {
        return 0;
    }
    if (board->data[x][y] == type)
    {
        return 1;
    }

    return 0;
}

void remove_bonus(game_t* game)
{
    int i;

    for (i = 0; i < REMOVE_COUNT; i++)
    {
        game->board.data[rand()%BOARD_WIDTH][rand()%BOARD_HEIGHT] = -1;
    }
    
}

int move_piece(board_t* board, direction_t dir)
{
    int x = board->sel_x;
    int y = board->sel_y;
    int x2 = x;
    int y2 = y;

    switch (dir)
    {
    case UP:
        y2--;
        break;
    case DOWN:
        y2++;
        break;
    case RIGHT:
        x2++;
        break;
    case LEFT:
        x2--;
        break;
    }
    
    swap_pieces(board, x, y, x2, y2);

    if (!check_moves(board, x, y) && !check_moves(board, x2, y2))
    {
       /* not a valid move -- put the gem back */
        swap_pieces(board, x2, y2, x, y);   
        return 0;
    }
    return 1;
}

void swap_pieces(board_t* board, int x, int y, int x2, int y2)
{

   /* we should always be inside the board */
    assert(x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT);
    assert(x2 >= 0 && x2 < BOARD_WIDTH && y2 >= 0 && y2 < BOARD_HEIGHT);
    /* if we're pointing at the same element, it gets zeroed */
    assert(x != x2 || y != y2);

    board->data[x][y] ^= board->data[x2][y2];
    board->data[x2][y2] ^= board->data[x][y];
    board->data[x][y] ^= board->data[x2][y2];
}

void draw_board(board_t* board, screen_t* screen)
{
    int x, y;
    
    for (y = 0; y < BOARD_HEIGHT; y++)
    {
        for (x = 0; x < BOARD_WIDTH; x++)
        {
            if (board->data[x][y] == -1) /* empty */
                continue;
            draw_canvas(screen->tileset.sprites[board->data[x][y]],
                        screen, x*PIECE_WIDTH+LEFT_BORDER, y*PIECE_HEIGHT+TOP_BORDER);
        }
    }    
}

void draw_selector(board_t* board, screen_t* screen)
{
    if (board->sel_x == -1) /* no selected piece */
       return;
        draw_canvas(screen->selector, screen,
                    board->sel_x*PIECE_WIDTH+TOP_BORDER,
                    board->sel_y*PIECE_HEIGHT+LEFT_BORDER);
}

int find_move(game_t* game, screen_t* screen)
{
    int x, y;
    
    for (y = 0; y < BOARD_HEIGHT; y++)
        for (x = 0; x < BOARD_WIDTH; x++)
        {
           if (y >= 1) {
            swap_pieces(&(game->board), x, y, x, y-1);
            if (check_moves(&(game->board), x, y))
            {
                swap_pieces(&(game->board), x, y, x, y-1);
                return 1;
            }
            swap_pieces(&(game->board), x, y, x, y-1);
           }

           if (y < BOARD_HEIGHT - 1) {
            swap_pieces(&(game->board), x, y, x, y+1);
            if (check_moves(&(game->board), x, y))
            {
                swap_pieces(&(game->board), x, y, x, y+1);
                return 1;
            }
            swap_pieces(&(game->board), x, y, x, y+1);
           }

           if (x >= 1) {
            swap_pieces(&(game->board), x, y, x-1, y);
            if (check_moves(&(game->board), x, y))
            {
                swap_pieces(&(game->board), x, y, x-1, y);
                return 1;
            }
            swap_pieces(&(game->board), x, y, x-1, y);
           }

           if (x < BOARD_WIDTH - 1) {
            swap_pieces(&(game->board), x, y, x+1, y);
            if (check_moves(&(game->board), x, y))
            {
                swap_pieces(&(game->board), x, y, x+1, y);
                return 1;
            }
            swap_pieces(&(game->board), x, y, x+1, y);
        }
        }

    //draw_text("NO MORE MOVES!!", 130, 200, screen);
    draw_canvas(screen->gameOver, screen, 0, 0);
    SDL_Flip(screen->screen);
    usleep(3000000);
    
    return 0;
}
