#include <ncurses.h>
#include <unistd.h>

void init_screen();

int main()
{
    init_screen();
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
    attron(A_BLINK);
    while(1)
    {
        printw("Hello there\n");
        sleep(1);
        refresh();
    }
    attroff(stdscr);
    return;
}
