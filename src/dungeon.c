#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void init_screen();

struct _box {

    short line, column;

    char type;

};

void create_box(int);

int main()
{
    srand(time(NULL));
    char ch;
    int side, counter = 10;
    WINDOW* my_win = newwin(10, 10, 5, 5);
    init_screen();
    printw("Give me the side: ");
    scanw("%d", &side);
    clear(); // Clear the screen from the prompt
    while(counter > 0)
    {
        create_box(side);
        counter--;
    }

    while((ch = getch()) != 'q');
    
    endwin();
    return 0;
}

void init_screen()
{
    char ch;
    initscr();
    curs_set(0);
    start_color();
    noecho();
    cbreak();
    refresh();
    return;
}

void create_box(int SIDE) 
{
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);
    int x = (rand() % maxx) / 2;
    int y = (rand() % maxy) / 2;
    mvhline(y, x, '*', SIDE);
    mvvline(y, x + (SIDE - 1), '*', SIDE);
    mvvline(y, x, '*', SIDE);
    mvhline(y + (SIDE - 1), x, '*', SIDE);
    return;
}
