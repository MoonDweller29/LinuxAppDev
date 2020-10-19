#include <ncurses.h>
#include <locale.h>
#include "pcre_utils.h"

#define DX 3
#define ONLELINE 3
#define MAXSTR 80

void update(WINDOW *win)
{
    box(win, 0, 0);
    wrefresh(win);
}

void clear_win(WINDOW *win)
{
    werase(win);
    update(win);
}

int main() {
    WINDOW *winA, *winB, *winO;
    char inA[MAXSTR], inB[MAXSTR];
    int half;

    setlocale(LC_ALL,"");

    initscr();
    cbreak();
    printw("Input:");
    refresh();

    half = (COLS-2*DX)/2;
    winA = newwin(ONLELINE, half, DX, DX);
    winB = newwin(ONLELINE, half, DX, DX+half);
    winO = newwin(LINES-ONLELINE-DX*2, (COLS-2*DX), DX+ONLELINE, DX);
    keypad(winA, TRUE);
    keypad(winB, TRUE);
    scrollok (winO, TRUE);
    wmove(winO, 1, 0);
    update(winA);
    update(winB);
    update(winO);
    do {
        clear_win(winA); clear_win(winB);
        mvwgetnstr(winA, 1, 1, inA, MAXSTR);
        werase(winB); update(winB);
        mvwgetnstr(winB, 1, 1, inB, MAXSTR);
        wprintw(winO, " Entered: %s : %s\n", inA, inB);
        pcre_find(inA, inB, winO);
        clear_win(winA); clear_win(winB);
        update(winO);
    } while(*inA);

    endwin();

}