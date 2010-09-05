#ifndef _BOARD_H_
#define _BOARD_H_

#include "graphics.h"
#include "game.h"

/* ************************************************************************ */
/* ENUM direction_t */
/* This enum provides a more intuitive means to relate a direction */
/* ************************************************************************ */
typedef enum {UP, LEFT, RIGHT, DOWN} direction_t;

/* ************************************************************************ */
/* FUNCTION create_board */
/* fills the given board with random pieces */
/* ************************************************************************ */
void create_board(board_t* board);

/* ************************************************************************ */
/* FUNCTION draw_board */
/* draw board onto screen with the top left corner of board at (x, y) */
/* ************************************************************************ */
void draw_board(board_t* board, screen_t* screen);

/* ************************************************************************ */
/* FUNCTION draw_selector */
/* draw an outline around the piece that is selected */
/* ************************************************************************ */
void draw_selector(board_t* board, screen_t* screen);

/* ************************************************************************ */
/* FUNCTION move_piece */
/* Move the piece at x, y on board in the direction of dir */
/* The direction must be legal */
/* ************************************************************************ */
int move_piece(board_t* board, direction_t dir);

/* ************************************************************************ */
/* FUNCTION find_move */
/* returns 0 if there are no moves left */
/* returns 1 otherwise */
/* ************************************************************************ */
int find_move(game_t* game, screen_t* screen);

/* ************************************************************************ */
/* FUNCTION update_board */
/* Calls: */
/* 1. remove_matches() */
/* 2. apply_graivty() */
/* 3. refill_board() */
/* until there are no more pieces to remove */
/* ************************************************************************ */
void update_board(game_t* game, screen_t* screen);

/* ************************************************************************ */
/* FUNCTION remove_matches */
/* scans the board for 3 or more of the same jewel in a line and applys */
/* points to the players score */
/* returns 1 if there were matches made */
/* returns 0 if there were none */
/* ************************************************************************ */
int remove_matches(game_t* game, screen_t* screen, int mult);

/* ************************************************************************ */
/* FUNCTION remove_matches */
/* Causes pieces to fall if there is no piece directly below them until */
/* each piece is "settled" */
/* ************************************************************************ */
void apply_gravity(board_t* board);

/* ************************************************************************ */
/* FUNCTION refill_board */
/* adds random pieces to the board in spaces that are empty */
/* (they fall from above) */
/* ************************************************************************ */
void refill_board(board_t* board);

/* ************************************************************************ */
/* FUNCTION remove_bonus */
/* remove 8? random jewels and update the board */
/* ************************************************************************ */
void remove_bonus(game_t* game);

/* ************************************************************************ */
/* FUNCTION write_board */
/* write the *binary* data of the board to a file */
/* piece location only, the tileset is loaded separately */
/* ************************************************************************ */
void write_board(board_t* board, const char* filename);

/* ************************************************************************ */
/* FUNCTION read_board */
/* read the *binary* data of the board from a file */
/* piece location only, the tileset is loaded separately */
/* ************************************************************************ */
void read_board(board_t* board, const char* filename);

#endif
