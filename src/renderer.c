#include "../include/renderer.h"
#include "../include/card.h"
#include "../include/ui.h"
#include <ncurses.h>

#define DEALER_ROW 2
#define DEALER_COL 2
#define PLAYER_ROW 15
#define PLAYER_COL 2
#define STATUS_ROW 20
#define STATUS_COL 2
#define PROMPT_ROW 22
#define PROMPT_COL 2
#define TOTALS_ROW 17
#define TOTALS_COL 30

void renderer_init(void) {
    ui_init();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
}

void renderer_shutdown(void) {
    ui_shutdown();
}

void renderer_clear(void) {
    ui_clear_frame();
}

void renderer_refresh(void) {
    ui_refresh_frame();
}

static void renderer_draw_hand(const Hand *hand, int row, int col, int hide_first_card) {
    if (!hand || hand->count == 0)
        return;

    const char *owner_name = (hand->owner == HAND_DEALER) ? "Dealer" : "Player";
    mvprintw(row - 2, col + 3, "%s", owner_name);

    for (int i = 0; i < hand->count; i++) {
        int hide = (hide_first_card && i == 0 && hand->owner == HAND_DEALER) ? 1 : 0;
        card_draw(&hand->cards[i], row + i, col, hide);
    }
}

void renderer_draw_player_hand(const Hand *player) {
    renderer_draw_hand(player, PLAYER_ROW, PLAYER_COL, 0);
}

void renderer_draw_dealer_hand(const Hand *dealer, int show_hidden) {
    renderer_draw_hand(dealer, DEALER_ROW, DEALER_COL, !show_hidden);
}

void renderer_draw_status_message(const char *message) {
    if (!message)
        return;
    mvprintw(STATUS_ROW, STATUS_COL, "%s", message);
}

void renderer_draw_prompt(const char *prompt) {
    if (!prompt)
        return;
    mvprintw(PROMPT_ROW, PROMPT_COL, "%s", prompt);
}

void renderer_draw_totals(int player_total, int dealer_total) {
    mvprintw(TOTALS_ROW, TOTALS_COL, "Player: %d | Dealer: %d", player_total, dealer_total);
}

void renderer_draw_game_state(const Hand *player, const Hand *dealer, GameState state) {
    renderer_draw_dealer_hand(dealer, 0);
    renderer_draw_player_hand(player);

    switch (state) {
        case STATE_PLAYER_TURN:
            renderer_draw_prompt("[A] HIT   |   [S] STAND");
            break;

        case STATE_DEALER_TURN:
            renderer_draw_prompt("Dealers turn ...");
            break;

        case STATE_ROUND_OVER:
            renderer_draw_prompt("[P] Play Again    |   [Q] Quit");
            break;

        case STATE_MENU:
        case STATE_START:
            break; // todo
    }
}

void renderer_draw_round_result(const RoundOutcome *outcome, int player_total, int dealer_total) {
    const char *result_text = "";

    switch (outcome->result) {
        case RESULT_PLAYER_WIN:
            result_text = "PLAYER WINS";
            break;

        case RESULT_DEALER_WIN:
            result_text = "DEALER WINS";
            break;

        case RESULT_PUSH:
            result_text = "PUSH - TIE";
            break;
    }

    mvprintw(STATUS_ROW, STATUS_COL, "%s", result_text);
    renderer_draw_totals(player_total, dealer_total);
}

void renderer_draw_menu(void) {
    mvprintw(10, 5, "=== Blackjack ===");
    mvprintw(12, 5, "[P] Play");
    mvprintw(13, 5, "[Q] Quit");
}
