#ifndef _BONUS_H_
#define _BONUS_H_

#include "graphics.h"
#include "game.h"

#define REMOVE_COUNT 8

/* ************************************************************************ */
/* FUNCTION draw_bonus */
/* draw the bonus indicator to the screen */
/* ************************************************************************ */
void draw_bonus(game_t* game, screen_t* screen, int x, int y);

/* ************************************************************************ */
/* FUNCTION apply_bonus */
/* call remove_bonus and calculate the new bonus */
/* ************************************************************************ */
void apply_bonus(game_t* game, screen_t* screen);

#endif
