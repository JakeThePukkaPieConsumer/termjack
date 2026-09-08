#include "../include/input.h"

InputAction input_process(int ch) {
    switch (ch) {
        case 'a':
        case 'A':
            return INPUT_HIT;

        case 's':
        case 'S':
            return INPUT_STAND;

        case 'p':
        case 'P':
            return INPUT_PLAY_AGAIN;

        case 'm':
        case 'M':
            return INPUT_MENU;

        case 'q':
        case 'Q':
            return INPUT_QUIT;

        default:
            return INPUT_NONE;
    }
}
