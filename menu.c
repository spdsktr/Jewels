#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

#include "menu.h"
#include "graphics.h"

#define SLOT_INC 70
#define SLOT1 130
#define SLOT2 SLOT1 + SLOT_INC
#define SLOT3 SLOT2 + SLOT_INC
#define SLOT4 SLOT3 + SLOT_INC
#define TILESET_LEFT 100
#define TILESET_TOP 160
//#define TILESET_HEIGHT 30
#define TILESET_HEIGHT 40
#define TILESET_MAX 6

#define UP_LEFT 100
#define DOWN_LEFT UP_LEFT
#define UP_TOP 105
#define DOWN_TOP 410

typedef enum {NEW, LOAD, TILESET, CREDITS, NONE} state_t;

void get_tilesets();
int process_state(state_t state, game_t* game, screen_t* screen);
int check_state(state_t* state);
void draw_menu(state_t state, screen_t* screen);
void draw_credits(screen_t* screen);
int tileset_mouse_click(screen_t* screen, SDL_MouseButtonEvent click);
void draw_tileset(screen_t* screen);
int get_menu_item(void);

static canvas_t* menu_tile;
static canvas_t* menu_title;
static canvas_t* menu_options[4][2];
static char* tilesets[8192];
static int t_sel = 0;
static int t_count = -1;

int menu(game_t* game, screen_t* screen)
{
    state_t state = NONE;
    int i, val;
    
    menu_tile = IMG_Load("gfx/menutile.png");
    menu_title = IMG_Load("gfx/menutitle.png");
    menu_options[0][0] = IMG_Load("gfx/menunew.png");
    menu_options[1][0] = IMG_Load("gfx/menuload.png");
    menu_options[2][0] = IMG_Load("gfx/menutileset.png");
    menu_options[3][0] = IMG_Load("gfx/menucredits.png");
    menu_options[0][1] = IMG_Load("gfx/menunew_s.png");
    menu_options[1][1] = IMG_Load("gfx/menuload_s.png");
    menu_options[2][1] = IMG_Load("gfx/menutileset_s.png");
    menu_options[3][1] = IMG_Load("gfx/menucredits_s.png");
    //SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
    SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);
    SDL_WarpMouse(0,0);
    while(1)
    {
        state = get_menu_item();
        draw_menu(state, screen);
        val = check_state(&state);
        draw_menu(state, screen);
        if(val==1)
        {
            if (process_state(state, game, screen))
                break;
        }
        else if(val==2)
            return 0;
    }
    
    SDL_FreeSurface(menu_tile);
    SDL_FreeSurface(menu_title);
    for (i = 0; i < 4; i++)
    {
        SDL_FreeSurface(menu_options[i][0]);
        SDL_FreeSurface(menu_options[i][1]);
    }
    return 1;
}

int process_state(state_t state, game_t* game, screen_t* screen)
{
    SDL_Event event;
    
    switch(state)
    {
    case NONE:
        break;
    case LOAD:
        if (load_game(game))
            return 1;
    case NEW:
        new_game(game);
        return 1;
    case TILESET:
        get_tilesets();
				draw_tileset(screen);
        
        while(1)
        {
            while(SDL_WaitEvent(&event))
            {
                switch(event.type)
                {
                case SDL_MOUSEBUTTONUP:
                    if (tileset_mouse_click(screen, event.button))
                    {
                    	SDL_WarpMouse(0,0);
                    	return 0;
                    }
                    break;
                case SDL_QUIT:
                    exit(0);
                }
            }
        }
    case CREDITS:
        draw_credits(screen);
        while(1)
        {
           while(SDL_WaitEvent(&event))
           {
                switch(event.type)
                {
                //case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                		SDL_WarpMouse(0,0);
                    return 0;
                case SDL_QUIT:
                    exit(0);
                }
            }
        }
    }
    return 0;
}

void get_tilesets()
{
    int i;
    struct dirent **namelist;
    
    t_count = scandir("tilesets", &namelist, 0, alphasort);
    if (t_count < 0)
    {
        printf("error loading the tileset directory!\n");
	return;
    }

    free(namelist[0]); //.
    free(namelist[1]); //..
    for (i=2; i<t_count; i++)
    {
        strcpy((char*) tilesets+(i-2)*256, namelist[i]->d_name);
	free(namelist[i]);
    }
    free(namelist);
    t_count -=2; //no . and ..
}

void draw_tileset(screen_t* screen)
{
    int x, y;
    canvas_t* up;
    canvas_t* down;

    up = IMG_Load("gfx/jewel4.png");
    down = IMG_Load("gfx/jewel3.png");

    for(y = 0; y < SCREEN_HEIGHT; y += menu_tile->h)
    {
        for(x = 0; x < SCREEN_WIDTH; x += menu_tile->w)
	{
	    draw_canvas(menu_tile, screen, x, y);
	}
    }
    draw_canvas(menu_title, screen, 0, 0);
    draw_canvas(up, screen, UP_LEFT, UP_TOP);
    draw_canvas(down, screen, DOWN_LEFT, DOWN_TOP);
    
    for (x=t_sel, y=0; x<t_count && y<TILESET_MAX; x++, y++)
        draw_text((char*) tilesets+x*256, TILESET_LEFT, TILESET_TOP+y*TILESET_HEIGHT, screen);
    
    SDL_Flip(screen->screen);

    SDL_FreeSurface(up);
    SDL_FreeSurface(down);
}

int tileset_mouse_click(screen_t* screen, SDL_MouseButtonEvent click)
{
    int sel;
    char name[256];
    int x, y;

    x = click.x;
    y = click.y;

    if (x>UP_LEFT && x<UP_LEFT+PIECE_WIDTH && y>UP_TOP && y<UP_TOP+PIECE_HEIGHT && t_sel > 0)
    {
        t_sel--;
	draw_tileset(screen);
	return 0;
    }
    
    if (x>DOWN_LEFT && x<DOWN_LEFT+PIECE_WIDTH && y>DOWN_TOP && y<DOWN_TOP+PIECE_HEIGHT && t_count - t_sel > TILESET_MAX)
    {
        t_sel++;    
	draw_tileset(screen);
	return 0;
    }

    x -= TILESET_LEFT;
    y -= TILESET_TOP;   
    if (x < 0 || y < 0 || y > t_count*TILESET_HEIGHT || y > TILESET_MAX*TILESET_HEIGHT) return 0;       

    sel = y/TILESET_HEIGHT+t_sel;
    
    sprintf(name, "tilesets/%s", (char*) tilesets+256*sel);
    reload_tileset(name, &(screen->tileset));
    
    return 1;
}

int get_menu_item(void)
{
    int y,x, i;

    SDL_GetMouseState(&x, &y);
    
    for (i = 3; i >=0; i--)
        if (y > SLOT1+i*SLOT_INC && x > 130 && x < 525)
        {
            return i;
        }
    
    return NONE;
}

int check_state(state_t* state)
{
    unsigned int i;
    SDL_Event event;

    (*state) = get_menu_item();

    for(;;) {
       SDL_WaitEvent(&event);
        switch(event.type)
        {
	        case SDL_MOUSEBUTTONDOWN:	        	  
          	i = get_menu_item();
         		/* menu item hasn't changed? ignore it */
         		if (*state != i) 
         		{
            	*state = i;
            	return 0;
         		}
             	
          break;
	        case SDL_MOUSEBUTTONUP:
	        		
	            if ((*state) != NONE)
	                return 1;
	            break;
	        case SDL_QUIT:	            
	            return 2;
	        
//	        case SDL_MOUSEMOTION:
//	            while(SDL_WaitEvent(&event) && (event.type == SDL_MOUSEMOTION))
//	            {
//	               i = get_menu_item();
//	               /* menu item hasn't changed? ignore it */
//               if (*state != i) {
//	                  *state = i;
//	                  return 0;
//	               }
//	            }
//	            SDL_PushEvent(&event);
	            
        }
    }
    /* not reached */
    return 0;
}

void draw_menu(state_t state, screen_t* screen)
{
    int x, y;
    unsigned int i;
    int sel;

    for(y = 0; y < SCREEN_HEIGHT; y += menu_tile->h)
    {
        for(x = 0; x < SCREEN_WIDTH; x += menu_tile->w)
        {
            draw_canvas(menu_tile, screen, x, y);
        }
    }
    draw_canvas(menu_title, screen, 0, 0);
    for(i = 0; i < 4; i++)
    {
        sel = 0;
        if (state == i) sel = 1;
        draw_canvas(menu_options[i][sel], screen, 125, SLOT1+SLOT_INC*i);
    }
    
    SDL_Flip(screen->screen);
}

void draw_credits(screen_t* screen)
{
    int x, y;
    
    for(y = 0; y < SCREEN_HEIGHT; y += menu_tile->h)
    {
        for(x = 0; x < SCREEN_WIDTH; x += menu_tile->w)
        {
            draw_canvas(menu_tile, screen, x, y);
        }
    }
    draw_canvas(menu_title, screen, 0, 0);
    
    draw_text("Designed By:", 140, 135, screen);
    draw_text("James Harris", 140, 170, screen);
    
    draw_text("Developed By:", 140, 222, screen);
    draw_text("Greg Hrebek (Syntactix LLC)", 140, 257, screen);
    
    draw_text("Original Game Created By:", 140, 309, screen);
    draw_text("Jonathan Bilodeau", 140, 344, screen);
    draw_text("Allison Gray", 140,379, screen);
    draw_text("Damian Gryski", 140,414, screen);
    SDL_Flip(screen->screen);
}
