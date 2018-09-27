/* TODO
* Do a purge funtion to a sdl rect 
*/

/*
* I must make a grid to determine where I have created or purged a mino.
*
*
*
*
*/

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#define BLOCK_WIDTH 32
#define BLOCK_HEIGHT 32

#define WIN_WIDTH 320
#define WIN_HEIGHT 640
#define GAME_WIDTH 320 /* Must be fixed according to BLOCK_WIDTH & HEIGHT */
#define GAME_HEIGHT 320

#define BACKGROUND_COLOR 0x000000
#define BLOCK_COLOR 0xff0000

#define NORTH 0
#define WEST 1
#define SOUTH 2
#define EAST 3 

#define T_TETROMINO 0
#define CUBE_TETROMINO 1
#define I_TETROMINO 2
#define L_TETROMINO 3
#define Z_TETROMINO 4

/* COLORS */

#define SDL_BACKGROUND 0x00, 0x00, 0x00, 0x00
#define SDL_WHITE 0xff, 0xff, 0xff, 0x00
#define SDL_BLACK 0x00, 0x00, 0x00, 0x00
#define SDL_RED 0xff, 0x00, 0x00, 0x00
#define SDL_GREEN 0x00, 0xff, 0x00, 0x00
#define SDL_BLUE 0x00, 0x00, 0xff, 0x00
#define SDL_FUCHSIA 0xff, 0x00, 0xff, 0x00

typedef struct _block { 
	int x, y;
	int w, h;
	uint8_t type;
} block;

typedef struct _pos {
	int x, y;
	int t_type;
} pos;


int
l_tetromino[4][3] = 
{
{ 0, 0, 0 },
{ 1, 0, 0 },
{ 1, 0, 0 },
{ 1, 1, 0 }
};

int
z_tetromino[4][3] = 
{
{ 0, 0, 0 },
{ 0, 0, 0 },
{ 1, 1, 0 },
{ 0, 1, 1 }
};

int
i_tetromino[4][3] = 
{
{ 0, 1, 0 },
{ 0, 1, 0 },
{ 0, 1, 0 },
{ 0, 0, 0 }
};

int
c_tetromino[4][3] = 
{
{ 0, 0, 0 },
{ 0, 0, 0 },
{ 1, 1, 0 },
{ 1, 1, 0 }
};

int
t_tetromino[4][3] = 
{
{ 0, 0, 0 },
{ 1, 1, 1 },
{ 0, 1, 0 },
{ 0, 1, 0 }
};

int
p_tetromino[4][3] = 
{
{ 0, 0, 0 },
{ 0, 1, 1 },
{ 0, 1, 0 },
{ 0, 1, 0 }
};

static int game_grid[WIN_WIDTH / 32][WIN_HEIGHT / 32]; 
static SDL_Rect tmp_rect;
static SDL_Rect game_area;
static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Surface *surface;
static SDL_Color block_color;
static SDL_Texture *tex;
static SDL_Rect _piece;
static pos tmpos;
static int startx = 0;
static int starty = 0;


pos draw_tetromino(int tetromino, int posx, int posy);



void create_win() {
	int i, j;
	window = SDL_CreateWindow("STetris",
			 SDL_WINDOWPOS_UNDEFINED,
			 SDL_WINDOWPOS_UNDEFINED,
			 WIN_WIDTH,
			 WIN_HEIGHT,
			 SDL_WINDOW_OPENGL);

	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, SDL_BACKGROUND);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	for(i = 0; i < (WIN_WIDTH / 32); i++)
	{
		for(j = 0; j < (WIN_HEIGHT / 32); j++)
		{
			game_grid[i][j] = 0;
		}
	}
	
	return;
	
}

void purge_tetromino(SDL_Rect rect, pos position)
{
	int i, j;
	SDL_SetRenderDrawColor(renderer, SDL_BACKGROUND);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 3; j++) {
			rect.x = position.x+j*BLOCK_WIDTH;
			rect.y = position.y+i*BLOCK_HEIGHT; 		
			SDL_RenderFillRect(renderer, &rect);
		}
	}
	//SDL_RenderPresent(renderer);
	return;
}

SDL_Rect move_tetromino(int dir, pos position)
{
	tmp_rect.w = BLOCK_WIDTH;
	tmp_rect.h = BLOCK_HEIGHT;
	tmp_rect.x = position.x;
	tmp_rect.y = position.y;
	position.t_type = I_TETROMINO;

	purge_tetromino(tmp_rect, position);
	draw_tetromino(position.t_type, position.x, position.y);

	return tmp_rect;

}

pos draw_tetromino(int tetromino, int posx, int posy)
{
	int i,j;
	pos cur_pos;
	cur_pos.x = posx;
	cur_pos.y = posy;
	cur_pos.t_type = tetromino;
	SDL_Rect recta;

	/* Defines the width and height of the blockz */
	recta.w = BLOCK_WIDTH;
	recta.h = BLOCK_HEIGHT;

	switch (tetromino) {
		case Z_TETROMINO :
			SDL_SetRenderDrawColor(renderer, SDL_WHITE);
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 3; j++) {
					if (z_tetromino[i][j] == 1) {
						recta.x = posx+j*BLOCK_WIDTH;
						recta.y = posy+i*BLOCK_HEIGHT; 		
						SDL_RenderFillRect(renderer, &recta);
					}
				}
			}
			break;
		case L_TETROMINO :
			SDL_SetRenderDrawColor(renderer, SDL_FUCHSIA);
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 3; j++) {
					if (l_tetromino[i][j] == 1) {
						recta.x = posx+j*BLOCK_WIDTH;
						recta.y = posy+i*BLOCK_HEIGHT; 		
						SDL_RenderFillRect(renderer, &recta);
					}
				}
			}

			break;
		case I_TETROMINO :
			SDL_SetRenderDrawColor(renderer, SDL_BLUE);
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 3; j++) {
					if (i_tetromino[i][j] == 1) {
						recta.x = posx+j*BLOCK_WIDTH;
						recta.y = posy+i*BLOCK_HEIGHT; 		
						SDL_RenderFillRect(renderer, &recta);
					}
				}
			}

			break;
		case T_TETROMINO :
			SDL_SetRenderDrawColor(renderer, SDL_RED);
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 3; j++) {
					if (t_tetromino[i][j] == 1) {
						recta.x = posx+j*BLOCK_WIDTH;
						recta.y = posy+i*BLOCK_HEIGHT; 		
						SDL_RenderFillRect(renderer, &recta);
					}
				}
			}
			break;
		case CUBE_TETROMINO :
			SDL_SetRenderDrawColor(renderer, SDL_GREEN);
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 3; j++) {
					if (c_tetromino[i][j] == 1) {
						recta.x = posx+j*BLOCK_WIDTH;
						recta.y = posy+i*BLOCK_HEIGHT; 		
						SDL_RenderFillRect(renderer, &recta);
					}
				}
			}
			
			break;
	}
	return cur_pos;
	
}


int main()
{
	pos coord;
	srand(time(NULL));
	SDL_Event e;
	SDL_Rect block;
	int quit = 0;
	int increment = 32;
	
	if(!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_SetError("Couldn't initialize video\n");
		SDL_Quit();
	}

	create_win();
	coord = draw_tetromino(rand() % 4, rand() % 320, -96);
	SDL_RenderPresent(renderer);
	while (1) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				SDL_Quit();
				break;
			}
			if (e.key.keysym.sym == SDLK_d && e.type == SDL_KEYDOWN)
			{
				SDL_Delay(100);
			//	move_tetromino(block, WEST, rand() % 4);
			}
			if (e.key.keysym.sym == SDLK_SPACE && e.type == SDL_KEYDOWN)
			{
				SDL_Log("The game starts!");
				
			}
			
		}	
		if (coord.y < 640)
		{
			SDL_Delay(300);
			move_tetromino(-1, coord);
			coord.y = coord.y + increment;
			SDL_RenderPresent(renderer);
			SDL_Log("%d", coord.y);
		}
	}
	return 0;
}
