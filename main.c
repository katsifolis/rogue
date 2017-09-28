#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct Player
{
int xPosition;
int yPosition;
short health;
short mana;
short strength;
short intelligence;
}player;

void StatusBar(player* user);
void MapSetUp();
player* newPlayer();

int main()
{
  //Initializations
  srand(time(NULL));
  int ch,  startx = 0, starty = 0;
  char checkMV;
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();

  MapSetUp();
  player* new = newPlayer();
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

  mvprintw(y = rand() % 28,x =  rand() % 28, "--------");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "--------");

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

void StatusBar(player* user)
{
  int i, y, x;
  mvprintw(38, 0, "Health:%d", user->health);
  mvprintw(38, 11, "Mana:%d", user->mana);
  return;
}






