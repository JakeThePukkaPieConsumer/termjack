#include "../include/game.h"
#include "../include/deck.h"
#include "../include/hand.h"
#include "../include/ui.h"
#include <ncurses.h>

#define FPS 60

void game_run(void) {
    Deck deck;
    Hand player = {.owner = HAND_PLAYER};
    init_deck(&deck);
    shuffle_deck(&deck);

    int running = 1;

    while (running) {
        ui_clear_frame();

        int ch = ui_get_input();
        if (ch == 'q')
            running = 0;

        if (ch == 'a') {
            Card new_card = draw_card(&deck);
            hand_add_card(&player, new_card);
        }

        if (ch == 'b') {
            hand_clear(&player);
        }

        for (int i = 0; i < player.count; i++) {
            card_draw(&player.cards[i], 0, 2 + i);
        }

        mvprintw(0, 20, "Total: %d", hand_total(&player));

        ui_refresh_frame();
        ui_wait_frame(FPS);
    }
}
