#pragma once

typedef enum {
    HEARTS,
    DIAMONDS,
    SPADES,
    CLUBS,
} Suit;

typedef struct {
    int rank;
    Suit suit;
} Card;

extern const char *suit_names[4];
extern const char *rank_names[14];

void card_draw(const Card *card, int row, int col, int hide);
int card_value(const Card *card);
