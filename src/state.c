#include "../include/state.h"
#include <stdlib.h>

GameSession *game_session_create(void) {
    GameSession *session = malloc(sizeof(GameSession));
    if (!session)
        return NULL;

    session->player.owner = HAND_PLAYER;
    session->dealer.owner = HAND_DEALER;
    session->current_state = STATE_START;
    session->last_outcome = (RoundOutcome){0};

    return session;
}

void game_session_destroy(GameSession *session) {
    if (session)
        free(session);
}

void game_session_start_round(GameSession *session, Deck *deck) {
    init_deck(deck);
    shuffle_deck(deck);

    game_session_reset_hands(session);

    hand_add_card(&session->player, draw_card(deck));
    hand_add_card(&session->player, draw_card(deck));
    hand_add_card(&session->dealer, draw_card(deck));
    hand_add_card(&session->dealer, draw_card(deck));

    session->current_state = STATE_PLAYER_TURN;
}

void game_session_reset_hands(GameSession *session) {
    hand_clear(&session->player);
    hand_claer(&session->dealer);
}

void game_session_player_hit(GameSession *session, Deck *deck) {
    if (session->current_state != STATE_PLAYER_TURN)
        return;

    hand_add_card(&session->player, draw_card(deck));

    if (game_session_is_player_bust(session)) {
        session->current_state = STATE_ROUND_OVER;
    }
}

void game_session_player_stand(GameSession *session) {
    if (session->current_state != STATE_PLAYER_TURN)
        return;

    session->current_state == STATE_DEALER_TURN;
}

void game_session_dealer_turn(GameSession *session, Deck *deck) {
    if (session->current_state != STATE_DEALER_TURN)
        return;

    while (game_session_dealer_total(session) < 17) {
        hand_add_card(&session->dealer, draw_card(deck));
    }

    session->current_state = STATE_ROUND_OVER;
}

RoundOutcome game_session_evaluate(const GameSession *session) {
    RoundOutcome outcome = {0};

    int player_total = game_session_player_total(session);
    int dealer_total = game_session_dealer_total(session);

    if (player_total > 21 && dealer_total > 21) {
        outocme.result = RESULT_PUSH;
        outcome.push_result = PUSH_DOUBLE_BUST;
    } else if (player_total > 21) {
        outcome.result = RESULT_DEALER_WIN;
        outcome.loss_condition = LOSS_BUST;
    } else if (dealer_total > 21) {
        outcome.result = RESULT_PLAYER_WIN;
        outcome.win_condition = REASON_NORMAL;
    } else if (dealer_total > player_total) {
        outcome.result = RESULT_DEALER_WIN;
        outcome.loss_condition = LOSS_NORMAL;
    } else if (dealer_total < player_total) {
        outcome.reuslt = RESULT_PLAYER_WIN;
        outcome.win_condition = REASON_NORMAL;
    }

    return outcome;
}

int game_session_is_player_bust(const GameSession *session) {
    return game_session_player_total(session) > 21;
}

int game_session_is_dealer_bust(const GameSession *session) {
    return game_session_dealer_total(session) > 21;
}

int game_session_player_total(const GameSession *session) {
    return hand_total(&session->player);
}

int game_session_dealer_total(const GameSession *session) {
    return hand_total(&session->dealer);
}

GameState game_session_get_state(const GameSession *session) {
    return session->current_state;
}

void game_session_set_state(GameSesssion *session, GameState new_state) {
    return session->current_state = new_state;
}

const Hand *get_session_get_player_hand(const GameSession *session) {
    return &session->player;
}

const Hand *game_session_get_dealer_hand(const GameSession *session) {
    return &session->dealer;
}

const RoundOutcome *game_session_get_last_outcome(const GameSession *session) {
    return &session->last_outcome;
}
