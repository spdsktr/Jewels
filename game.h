#ifndef _GAME_H_
#define _GAME_H_

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8
#define POINTS_PER_PIECE 5
//#define GFX_DELAY 500000
#define GFX_DELAY 500

#include "graphics.h"

/* ************************************************************************ */
/* TYPE board_t */
/* This type stores what pieces are in what location on a board */
/* ************************************************************************ */
typedef struct
{
    int data[BOARD_WIDTH][BOARD_HEIGHT];
    int sel_x;
    int sel_y;
} board_t;

/* ************************************************************************ */
/* STRUCT bonus_t */
/* This struct stores information about the bonus */
/* ************************************************************************ */
typedef struct
{
    int last;          /* the last score needed to obtain a bonus */
    int next;          /* the next score needed to obtain a bonus */
} bonus_t;

/* ************************************************************************ */
/* STRUCT score_t */
/* This struct stores information about the score and level */
/* ************************************************************************ */
typedef struct
{
    int score;            /* the player score */
    int level;            /* the players level */
} score_t;

/* ************************************************************************ */
/* STRUCT game_t */
/* This struct stores everything about the status of a current game */
/* ************************************************************************ */
typedef struct
{
    board_t board;     /* the layout of the current board */
    score_t score;         /* the current score */
    bonus_t bonus;         /* the next bonus point */
    int delay;
} game_t;

void new_game(game_t* game);
int load_game(game_t* game);
void save_game(game_t* game);

#endif
