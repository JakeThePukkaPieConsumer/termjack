#pragma once

typedef enum {
    RESULT_PLAYER_WIN,
    RESULT_DEALER_WIN,
    RESULT_PUSH,
} RoundResult;

typedef enum {
    REASON_NORMAL,              // Nothing special
    REASON_BLACKJACK,           // Natural
    REASON_TWENTY_ONE,          // 3+ Cards
    REASON_SUITED_BLACKJACK,    // Natural with same suit
    REASON_LUCKY_DOUBLE_DOWNER, // Double down but still won
    REASON_SPLIT_WIN,           // Split but still won
    REASON_FIVE_CARD_CHARLIE,   // 5 cards without a bust
} WinCondition;

typedef enum {
    LOSS_NORMAL,      // Nothing speical
    LOSS_BUST,        // Went over 21
    LOSS_SPLIT,       // Lost a split hand
    LOSS_DOUBLE_DOWN, // Lost a double down
} LossCondition;

void game_run(void);
