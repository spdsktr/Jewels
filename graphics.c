#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "graphics.h"

static canvas_t* font;

canvas_t* init_graphics()
{
    SDL_Surface *surface;

    /* Initialize SDL */
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    //surface = SDL_SetVideoMode(640, 480, 24, SDL_HWSURFACE | SDL_DOUBLEBUF);
    surface = SDL_SetVideoMode(720, 480, 32, 0);
    		    
    if (!surface) {
        printf("Could not set video mode: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_WM_SetCaption("gemz", "gemz");

    /* Initialize Fonts */
    font = IMG_Load("fonts/24P_Copperplate_Blue.png");
    InitFont(font);

    return surface;
}

void draw_canvas(canvas_t* canvas, screen_t* screen, int x, int y)
{
    rect_t rect;
    
    rect.x = x;
    rect.y = y;
    SDL_BlitSurface(canvas, NULL, screen->screen, &rect);
}

void draw_text(char* text, int x, int y, screen_t* screen)
{
    PutString(screen->screen, x, y, text);
}

int load_tileset(const char* filename, tileset_t* tileset)
{
    FILE* file;
    int i;
    char gfx_filename[40];
    canvas_t* tile;
    
    file = fopen(filename, "r");
    if (!file) {
        printf("Could not open tileset %s: %s\n", filename, strerror(errno));
        return 0;
    }
    for(i = 0; i < JEWEL_COUNT; i++)
    {
        fscanf(file, "%s", gfx_filename);
        tile = IMG_Load(gfx_filename);
        if (tile)
            tileset->sprites[i] = tile;
        else
        {
            printf("Invalid tileset %s\n", filename);
            return 0;
        }
    }
    
    fclose(file);
    return 1;
}

void reload_tileset(const char* filename, tileset_t* tileset)
{
    free_tileset(tileset);
    if (!load_tileset(filename, tileset))
        load_tileset("tilesets/default", tileset);
}
    

void free_tileset(tileset_t* tileset)
{
    int i;
    
    for(i = 0; i < JEWEL_COUNT; i++)
    {
        SDL_FreeSurface(tileset->sprites[i]);
    }
}

void free_font()
{
    SDL_FreeSurface(font);
}
