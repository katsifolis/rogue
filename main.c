#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct Player
{
  int xPosition;
  int yPosition;
  int health;
}player;
 
void MapSetUp();
void playerMov();
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
  starty = new->yPosition;
  startx = new->xPosition;
  while(1)
  {
    ch = getch();
    if(ch == KEY_DOWN)
    { 
      checkMV = mvinch(++starty, startx);
      if(checkMV == '-' || checkMV == '|')
      {
        continue;
      }else
      {
      move(starty,startx);
      mvprintw(starty, startx, ".");
      mvprintw(++starty, startx, "@");
      }
    }
    if(ch == KEY_UP)
    { 
      mvprintw(starty, startx, ".");
      mvprintw(--starty, startx, "@");
      move(starty,startx);
    }
    if(ch == KEY_RIGHT)
    { 
      mvprintw(starty, startx, ".");
      mvprintw(starty, ++startx, "@");
      move(starty,startx);
    }
    if(ch == KEY_LEFT)
    { 
      mvprintw(starty, startx, ".");
      mvprintw(starty, --startx, "@");
      move(starty,startx);
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
  mvprintw(y = 10,x = 10, "--------");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "|......|");
  mvprintw(++y, x, "--------");

  mvprintw(y = 27,x =  27, "--------");
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
  new->health = 20;
  mvprintw(new->yPosition,new->xPosition, "@");
 
  move(new->yPosition, new->xPosition);
 
  return new;
}







