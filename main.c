#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "nodes.h"

#define MAXSTRING 64   

// PRNG = Multiply with Carry
unsigned int rand32();
unsigned int randCMWC(struct cmwc_state *state);
void initCWMC(struct cmwc_state *state, unsigned int seed);
// end
void StatusBar(player* user);
void randMapSetUp(struct cmwc_state *state);
void MapSetUp();
monster* newMonster();
player* newPlayer();

int main()
{
  // PRNG
  struct cmwc_state cmwc;
  unsigned int seed = time(NULL);
  initCWMC(&cmwc, seed);
  printf("RANDOM NUMBRE: %u \n", randCMWC(&cmwc));

  //Initializatios
  srand(time(NULL));
  int ch,  startx = 0, starty = 0;
  char checkMV;
  initscr(); // Ncurses start 
  raw(); // Disable line buffering
  keypad(stdscr, TRUE); // Enables keys like F1, F2
  noecho(); 

  randMapSetUp(&cmwc);
  MapSetUp();
  player* new = newPlayer();
  monster* mon = newMonster();
  StatusBar(new);
  starty = new->yPosition;
  startx = new->xPosition;
  while(1)
  {
    ch = getch();
    if(ch == KEY_DOWN)
    { 
      switch(mvinch(starty + 1, startx))
      { 
        case('-'):
          move(starty, startx); //Move bitch get out the way
          break;
        default:
          mvprintw(starty, startx, ".");
          mvprintw(++starty, startx, "@");
          move(starty,startx);
      }
    }
    if(ch == KEY_UP)
    { 
      switch(mvinch(starty - 1, startx))
      { 
        case('-'):
          move(starty, startx); //Move bitch get out the way
          break;
        default:
          mvprintw(starty, startx, ".");
          mvprintw(--starty, startx, "@");
          move(starty,startx);
      }
    }
    if(ch == KEY_RIGHT)
    { 
      switch(mvinch(starty, startx + 1))
      { 
        case('|'):
          move(starty, startx); //Move bitch get out the way
          break;
        default:
          mvprintw(starty, startx, ".");
          mvprintw(starty, ++startx, "@");
          move(starty,startx);
      }
    }
    if(ch == KEY_LEFT)
    { 
      switch(mvinch(starty, startx - 1))
      { 
        case('|'):
          move(starty, startx); //Move bitch get out the way
          break;
        default:
          mvprintw(starty, startx, ".");
          mvprintw(starty, --startx, "@");
          move(starty,startx);
      }
    }
    if(ch == 'q') break;
  }

  refresh();
  endwin(); 
  return 0;

}

void randMapSetUp(struct cmwc_state *state)
{
  int x, y, maxy, maxx;
  getmaxyx(stdscr, maxy, maxx);
  mvprintw(y = randCMWC(state) % maxy , x = randCMWC(state) % maxx, ".");
  return;
}

void MapSetUp()
{
  int x, y;
  mvprintw(y = 8,x =  8, "--------");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "--------");
  mvprintw(y, x + rand() % 6, "+"); 

  return;

}

player* newPlayer()
{
  player *new;
  new = malloc(sizeof(player));
  new->yPosition = 12;
  new->xPosition = 13;
  new->health = rand() % 20;
  new->mana = rand() % 32;
  mvprintw(new->yPosition,new->xPosition, "@");

  move(new->yPosition, new->xPosition);

  return new;
}

monster* newMonster()
{
  monster* mon;
  mon = malloc(sizeof(monster));
  mon = malloc(sizeof(MAXSTRING));
  mon->health = rand() % 20;
  mon->mana = rand () % 32;
  

  return mon;
}
  

void StatusBar(player* user)
{

  int i, y, x;
  getmaxyx(stdscr, y, x);
  mvprintw(y - 1, 0, "Health:%d", user->health);
  mvprintw(y - 1, x / 6, "Mana:%d", user->mana);
  return;
}

// The random Generator

unsigned int rand32()
{
  unsigned int result = rand();
  return result << 16 | rand();
}   

void initCWMC(struct cmwc_state *state, unsigned int seed)
{
  srand(seed);
  for(int i = 0; i < CMWC_CYCLE; i++) state ->Q[i] = rand32();
  
  do state->c = rand32();
  while(state->c >= CMWC_C_MAX);
  state->i = CMWC_CYCLE - 1;
}
  

unsigned int randCMWC(struct cmwc_state *state)
{
  unsigned long const a = 1872; // As Marsaglia recommends
  unsigned int const m = 0xfffffffe;
  unsigned long t;
  unsigned long x;

  state->i = (state->i + 1) & (CMWC_CYCLE - 1);
  t = a * state->Q[state->i] + state->c;
  
  state->c = t >> 32;
  x = t + state->c;
  if(x < state->c)
  {
    x++;
    state->c++;
  }
  return state->Q[state->i] = m - x;
} 




