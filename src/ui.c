#include "../include/ui.h"

#include <ncurses.h>

void ui_init(void) {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
}

void ui_shutdown(void) {
    endwin();
}

void ui_clear_frame(void) {
    clear();
}

void ui_refresh_frame(void) {
    refresh();
}

void ui_wait_frame(int fps) {
    napms(1000 / fps);
}

int ui_get_input(void) {
    return getch();
}
