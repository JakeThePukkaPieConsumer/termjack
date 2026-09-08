#pragma once

typedef enum {
    RESULT_PLAYER_WIN,
    RESULT_DEALER_WIN,
    RESULT_PUSH,
} RoundResult;

void game_run(void);
