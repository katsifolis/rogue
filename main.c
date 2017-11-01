#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "nodes.h"

#define MAXSTRING 64   

void StatusBar(player* user);
void randMapSetUp();
void MapSetUp();
monster* newMonster();
player* newPlayer();

int main()
{

  //Initializatios
  srand(time(NULL));
  int ch,  startx = 0, starty = 0;
  char checkMV;
  initscr(); // Ncurses start 
  start_color(); // Color mode
  init_pair(1, COLOR_MAGENTA, 0);
  raw(); // Disable line buffering
  keypad(stdscr, TRUE); // Enables keys like F1, F2
  noecho(); 

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
	  attron(COLOR_PAIR(1));
          mvprintw(++starty, startx, "@");
	  attroff(COLOR_PAIR(1));
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

void randMapSetUp()
{
  int x, y, maxy, maxx;
  getmaxyx(stdscr, maxy, maxx);
  mvprintw(y = rand() % maxy , x = rand() % maxx, ".");
  return;
}

void MapSetUp()
{
  int x, y, xmax, ymax;
  getmaxyx(stdscr, ymax, xmax);
  mvprintw(y = 8,x = 8, "--------");
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




