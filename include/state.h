#pragma once

#include "./deck.h"
#include "./game.h"
#include "./hand.h"

typedef struct {
    Hand player;
    Hand dealer;
    GameState current_state;
    RoundOutcome last_outcome;
} GameSession;

GameSession *game_session_create(void);
void game_session_destroy(GameSession *session);

void game_session_start(GameSession *session, Deck *deck);
void game_session_reset_hands(GameSession *session);

void game_session_dealer_turn(GameSession *session, Deck *deck);

RountOutcome game_session_evaluate(const GameSession *session);
int game_session_is_player_bust(const GameSession *session);
int game_session_is_dealer_bust(const GameSession *session);
int game_session_player_total(const GameSession *session);
int game_session_dealer_total(const GameSession *session);

GameState game_session_get_state(const GameSession *session);
void game_session_set_state(GameSession *session, GameState new_state);
const Hand *game_session_get_player_hand(const GameSession *session);
const Hand *game_session_get_dealer_hand(const GameSession *session);
