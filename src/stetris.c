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
#define WIN_HEIGHT 480

#define BACKGROUND_COLOR 0x000000
#define BLOCK_COLOR 0xff0000

#define NORTH 0
#define WEST 1
#define SOUTH 2
#define EAST 3 

#define T_TETROMINO 0
#define C_TETROMINO 1
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

char *tetromino[5] =
{"t_tetromino", "c_tetromino", "i_tetromino", "l_tetromino", "z_tetromino"};

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
{ 0, 1, 0 }
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
{ 0, 0, 0 }
};

int
p_tetromino[4][3] = 
{
{ 0, 0, 0 },
{ 0, 1, 1 },
{ 0, 1, 0 },
{ 0, 1, 0 }
};

/* STAT */

static int game_grid[WIN_HEIGHT / 32][WIN_WIDTH / 32]; 
static SDL_Rect tmp_rect;
static SDL_Rect game_area;
static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Surface *surface;
static SDL_Color block_color;
static SDL_Texture *tex;
static SDL_Rect _piece;
static pos tmpos;
static int line_count = 0;
static int startx = 0;
static int starty = 0;

/* FUNC */

pos draw_tetromino(int tetromino, int posx, int posy);
void create_win();
void purge_tetromino(int type, SDL_Rect rect, pos position);
SDL_Rect move_tetromino(int dir, pos position);



void create_win() 
{
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
	for(i = 0; i < (WIN_HEIGHT / 32); i++)
	{
		for(j = 0; j < (WIN_WIDTH / 32); j++)
		{
			game_grid[i][j] = 0;
		}
	}
	for(i = 0; i < (WIN_HEIGHT / 32); i++)
	{
		for(j = 0; j < (WIN_WIDTH / 32); j++)
		{
			printf("%d ", game_grid[i][j]);
		}
		puts("");
	}
	
	return;
	
}

void purge_tetromino(int type, SDL_Rect rect, pos position)
{
	int i, j;
	SDL_SetRenderDrawColor(renderer, SDL_BACKGROUND);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 3; j++) {
			rect.x = position.x+j*BLOCK_WIDTH;
			rect.y = position.y+i*BLOCK_HEIGHT - 32; 		
			if (type == T_TETROMINO)
			{
				if (t_tetromino[i][j] == game_grid[rect.y / 32][rect.x / 32])
				{	
					SDL_RenderFillRect(renderer, &rect);
					game_grid[rect.y / 32][rect.x / 32] = 0;
				}
			} else if (type == C_TETROMINO) {
			
				if (c_tetromino[i][j] == game_grid[rect.y / 32][rect.x / 32])
				{
					SDL_RenderFillRect(renderer, &rect);
					game_grid[rect.y / 32][rect.x / 32] = 0;
				}
			} else if (type == I_TETROMINO) {
				if (i_tetromino[i][j] == game_grid[rect.y / 32][rect.x / 32])
				{
					SDL_RenderFillRect(renderer, &rect);
					game_grid[rect.y / 32][rect.x / 32] = 0;
				}
			} else if (type == L_TETROMINO) {
				if (l_tetromino[i][j] == game_grid[rect.y / 32][rect.x / 32])
				{
					SDL_RenderFillRect(renderer, &rect);
					game_grid[rect.y / 32][rect.x / 32] = 0;
				}
			} else if (type == Z_TETROMINO) {
				if (z_tetromino[i][j] == game_grid[rect.y / 32][rect.x / 32])
				{
					SDL_RenderFillRect(renderer, &rect);
					game_grid[rect.y / 32][rect.x / 32] = 0;
				}
			} 
		}
	}
	return;
}

SDL_Rect move_tetromino(int dir, pos position)
{
	tmp_rect.w = BLOCK_WIDTH;
	tmp_rect.h = BLOCK_HEIGHT;
	tmp_rect.x = position.x;
	tmp_rect.y = position.y;
//	position.t_type = Z_TETROMINO;
	
	purge_tetromino(position.t_type, tmp_rect, position);
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
						game_grid[recta.y / 32][recta.x / 32] = 1;
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
						game_grid[recta.y / 32][recta.x / 32] = 1;
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
						game_grid[recta.y / 32][recta.x / 32] = 1;
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
						game_grid[recta.y / 32][recta.x / 32] = 1;
					}
				}
			}
			break;
		case C_TETROMINO :
			SDL_SetRenderDrawColor(renderer, SDL_GREEN);
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 3; j++) {
					if (c_tetromino[i][j] == 1) {
						recta.x = posx+j*BLOCK_WIDTH;
						recta.y = posy+i*BLOCK_HEIGHT; 		
						SDL_RenderFillRect(renderer, &recta);
						game_grid[recta.y / 32][recta.x / 32] = 1;
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
	coord.x = 0;
	coord.y = 0;
	coord.t_type = I_TETROMINO;
	srand(time(NULL));
	SDL_Event e;
	SDL_Rect block;
	int quit = 0;
	int increment = 32;
	int line_count = 0;
	
	if(!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_SetError("Couldn't initialize video\n");
		SDL_Quit();
	}

	create_win();
	//coord = draw_tetromino(rand() % 4, rand() % 320, 0);
	SDL_RenderPresent(renderer);
	SDL_Delay(200);
	while (1) {
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) {
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				SDL_Quit();
				break;
			}
			if (e.key.keysym.sym == SDLK_p && e.type == SDL_KEYDOWN)
			{
				SDL_Delay(100);
				quit  = 1;
			}
			if (e.key.keysym.sym == SDLK_r && e.type == SDL_KEYDOWN)
			{
				SDL_Delay(100);
				quit  = 0;
			}
		}
		if(!quit)
		{
			SDL_Delay(200);
			move_tetromino(-1, coord);
			coord.y = coord.y + increment;
			SDL_RenderPresent(renderer);
			SDL_Log("%d", coord.x);
			int i = 0, j = 0, flag = 0;
			for (i = 0; i < (WIN_HEIGHT / 32); i++)
			{
				for (j = 0; j < (WIN_WIDTH / 32); j++)
				{
					if (line_count == 11)
					{
						coord.y = 0;
						coord.x = coord.x + 32;
						coord.t_type = I_TETROMINO;
						line_count = -1;
					}
					printf("%d ", game_grid[i][j]);
				}
				printf("\n");
			}
			line_count++;
			printf("-- (%d) --\n", line_count);

		}
	}
	
	return 0;
}
