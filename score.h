#ifndef _SCORE_H_
#define _SCORE_H_

#include "graphics.h"
#include "game.h"

/* ************************************************************************ */
/* FUNCTION draw_score */
/* draw the score to the screen */
/* ************************************************************************ */
void draw_score(game_t* game, screen_t* screen, int x, int y);

/* ************************************************************************ */
/* FUNCTION draw_level */
/* draw the level to the screen */
/* ************************************************************************ */
void draw_level(game_t* game, screen_t* screen, int x, int y);

#endif
