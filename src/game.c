#include "../include/game.h"
#include "../include/deck.h"
#include "../include/hand.h"
#include "../include/ui.h"
#include <ncurses.h>

#define FPS 60

void game_run(void) {
    Deck deck;

    Hand player = {.owner = HAND_PLAYER};
    Hand dealer = {.owner = HAND_DEALER};

    GameState state = STATE_START;
    int running = 1;

    while (running) {
        ui_clear_frame();

        int ch = ui_get_input();
        if (ch == 'q')
            running = 0;

        }

        ui_refresh_frame();
        ui_wait_frame(FPS);
    }
}
