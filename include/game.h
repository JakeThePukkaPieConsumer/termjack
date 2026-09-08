#pragma once

typedef enum {
    STATE_START,
    STATE_PLAYER_TURN,
    STATE_DEALER_TURN,
    STATE_ROUND_OVER,
} GameState;

typedef enum {
    RESULT_NONE,
    RESULT_PLAYER_WIN,
    RESULT_DEALER_WIN,
    RESULT_PUSH,
    RESULT_PLAYER_BUST,
    RESULT_DEALER_BUST
} RoundResult;

void game_run(void);
