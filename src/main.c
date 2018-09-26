#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "nodes.h"
#include "constant.h"


void status_bar(player* user);

WINDOW* init_screen();

void dungeon_setup();

void map_setup();

monster* new_monster();

player* new_player();

int main()
{
    //Initializatios
    int ch,  startx = 0, starty = 0;
    char checkMV;
    
    srand(time(NULL));

    WINDOW* newwin = init_screen();
    
    map_setup();
    player* new = new_player();
    monster* mon = new_monster();
    status_bar(new);
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


void map_setup()
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

player* new_player()
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

monster* new_monster()
{

    monster* mon;
    mon = malloc(sizeof(monster));
    mon = malloc(sizeof(MAXSTRING));
    mon->health = rand() % 20;
    mon->mana = rand () % 32;
    

    return mon;
}
  

void status_bar(player* user)
{
    int i, y, x;
    getmaxyx(stdscr, y, x);
    mvprintw(y - 1, 0, "Health:%d", user->health);
    mvprintw(y - 1, x / 6, "Mana:%d", user->mana);
    return;
}

WINDOW* init_screen()
{
    initscr(); // Ncurses start 
    curs_set(2); // Get rid of the little ass cursor
    raw(); // Disable line buffering
    keypad(stdscr, TRUE); // Enables keys like F1, F2
    noecho(); 

    uint8_t height, width, starty, startx;
    height = 5;
    width = 5;
    starty = (LINES - height) / 2;
    startx = (COLS - width) / 2;

    WINDOW* local_win = newwin(height, width, starty, startx);
    wrefresh(local_win);
    
    return local_win;
}
      
void dungeon_setup()
{

}

void generator()
{


}
    



