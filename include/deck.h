#pragma once

#include "card.h"

#define MAX_CARDS 52

typedef struct {
    Card cards[MAX_CARDS];
    int top_index;
    int count;
} Deck;

void init_deck(Deck *deck);
void shuffle_deck(Deck *deck);
Card draw_card(Deck *deck);
