#include "../include/deck.h"
#include <stdlib.h>

void init_deck(Deck *deck) {
    int index = 0;

    int suits = 4;
    int ranks = 13;

    for (int s = 0; s < suits; s++) {
        for (int r = 1; r <= ranks; r++) {
            deck->cards[index].suit = (Suit)s;
            deck->cards[index].rank = r;
            index++;
        }
    }

    deck->top_index = 0;
}

void shuffle_deck(Deck *deck) {
    for (int i = 0; i < MAX_CARDS; i++) {
        int swap_index = i + rand() % (MAX_CARDS - i);
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[swap_index];
        deck->cards[swap_index] = temp;
    }
}

Card draw_card(Deck *deck) {
    return deck->cards[deck->top_index++];
}
