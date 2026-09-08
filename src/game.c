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
    }

    return STATE_PLAYER_TURN;
}

static GameState state_dealer_turn(Deck *deck, Hand *dealer) {}

static GameState state_round_over(int ch, Deck *deck, Hand *player, Hand *dealer) {}

static RoundOutcome evaluate_round(const Hand *player, const Hand *dealer) {
    RoundOutcome outcome = {0};

    int player_total = hand_total(player);
    int dealer_total = hand_total(dealer);

    if (player_total > 21 && dealer_total > 21) {
        outcome.result = RESULT_PUSH;
    } else if (player_total > 21) {
        outcome.result = RESULT_DEALER_WIN;
    } else if (dealer_total > 21) {
        outcome.result = RESULT_PLAYER_WIN;
    } else if (dealer_total > player_total) {
        outcome.result = RESULT_DEALER_WIN;
    } else if (dealer_total < player_total) {
        outcome.result = RESULT_PLAYER_WIN;
    }

    return outcome;
}

static void draw_hand(const Hand *hand, int row, int col) {
    for (int i = 0; i < hand->count; i++) {
        mvprintw(row - 1, col + 3, "%s", hand->owner == HAND_DEALER ? "Dealer" : "Player");
        card_draw(&hand->cards[i], row + i, col, 0);
    }
}

static void game_render(GameState state, const Hand *player, const Hand *dealer) {
    draw_hand(player, 15, 2);
    draw_hand(dealer, 2, 2);

    switch (state) {
        case STATE_PLAYER_TURN:
            mvprintw(22, 2, "[A] Hit    |   [S] Stand");
            break;

        case STATE_ROUND_OVER:
            mvprintw(22, 2, "Press A to play again");
            break;
    }
}

void game_run(void) {
    Deck deck;

    Hand player = {.owner = HAND_PLAYER};
    Hand dealer = {.owner = HAND_DEALER};

    GameState state = STATE_START;
    RoundResult result = {0};
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
        }

        game_render(state, &player, &dealer);
        ui_refresh_frame();
        ui_wait_frame(FPS);
    }
}
