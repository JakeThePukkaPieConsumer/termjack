#pragma once

typedef enum {
    STATE_START,
    STATE_PLAYER_TURN,
    STATE_DEALER_TURN,
    STATE_ROUND_OVER,
} GameState;

void game_run(void);
