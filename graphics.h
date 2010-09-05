#ifndef _GFX_H_
#define _GFX_H_

#include "SDL.h"
#include "SDL_image.h"
#include "SFont.h"

//#define SCREEN_WIDTH 640
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 16
//#define TOP_BORDER 40
//#define LEFT_BORDER 40
//#define PIECE_WIDTH 50
//#define PIECE_HEIGHT 50
#define TOP_BORDER 25
#define LEFT_BORDER 25
#define PIECE_WIDTH 55
#define PIECE_HEIGHT 55

#define JEWEL_COUNT 7

typedef SDL_Surface canvas_t;
typedef SDL_Color color_t;
typedef SDL_Rect rect_t;
typedef struct
{
    canvas_t* sprites[JEWEL_COUNT];
} tileset_t;
typedef struct
{
    canvas_t* screen;
    tileset_t tileset;
    canvas_t* background;
    canvas_t* bonus;
    canvas_t* selector;
    canvas_t* bonusOverlay;
    canvas_t* gameOver;
} screen_t;

/* ************************************************************************ */
/* FUNCTION load_tileset */
/* reads a tileset from a file and returns it */
/* ************************************************************************ */
int load_tileset(const char* filename, tileset_t* tileset);
void reload_tileset(const char* filename, tileset_t* tileset);

/* ************************************************************************ */
/* FUNCTION free_tileset */
/* frees the current tileset */
/* ************************************************************************ */
void free_tileset(tileset_t* tileset);

/* ************************************************************************ */
/* FUNCTION free_font */
/* frees the font */
/* ************************************************************************ */
void free_font();

/* ************************************************************************ */
/* FUNCTION init_graphics */
/* initialize the graphics part of SDL */
/* ************************************************************************ */
canvas_t* init_graphics();

/* ************************************************************************ */
/* FUNCTION draw_canvas */
/* draw a canvas to the screen */
/* ************************************************************************ */
void draw_canvas(canvas_t* canvas, screen_t* screen, int x, int y);

/* ************************************************************************ */
/* FUNCTION draw_text */
/* draw text to the screen */
/* ************************************************************************ */
void draw_text(char* text, int x, int y, screen_t* screen);


#endif
