#include "../include/game.h"
#include "../include/deck.h"
#include "../include/hand.h"
#include "../include/ui.h"
#include <ncurses.h>

#define FPS 60

static GameState state_start(Deck *deck, Hand *player, Hand *dealer) {
    init_deck(deck);
    shuffle_deck(deck);

    hand_clear(player);
    hand_clear(dealer);

    hand_add_card(player, draw_card(deck));
    hand_add_card(player, draw_card(deck));
    hand_add_card(dealer, draw_card(deck));
    hand_add_card(dealer, draw_card(deck));

    return STATE_PLAYER_TURN;
}

static GameState state_player_turn(int ch, Deck *deck, Hand *player) {
    if (ch == 'a') {
        hand_add_card(player, draw_card(deck));
        if (hand_total(player) > 21)
            return STATE_ROUND_OVER;
    }

    if (ch == 's')
        return STATE_DEALER_TURN;

    return STATE_PLAYER_TURN;
}

static GameState state_dealer_turn(Deck *deck, Hand *dealer) {
    if (hand_total(dealer) < 17) {
        hand_add_card(dealer, draw_card(deck));
        return STATE_DEALER_TURN;
    }

    return STATE_ROUND_OVER;
}

static GameState state_round_over(int ch, Deck *deck, Hand *player, Hand *dealer) {
    if (ch == 'a')
        return STATE_START;

    return STATE_ROUND_OVER;
}

void game_run(void) {
    Deck deck;

    Hand player = {.owner = HAND_PLAYER};
    Hand dealer = {.owner = HAND_DEALER};

    GameState state = STATE_START;
    RoundResult result = RESULT_NONE;
    int running = 1;

    while (running) {
        ui_clear_frame();
        int ch = ui_get_input();

        if (ch == 'q')
            running = 0;

        switch (state) {
            case STATE_START:
                state = state_start(&deck, &player, &dealer);
                break;
            case STATE_PLAYER_TURN:
                state = state_player_turn(ch, &deck, &player);
                break;
            case STATE_DEALER_TURN:
                state = state_dealer_turn(&deck, &dealer);
                break;
            case STATE_ROUND_OVER:
                state = state_round_over(ch, &deck, &player, &dealer);
                break;
        }

        ui_refresh_frame();
        ui_wait_frame(FPS);
    }
}
