#include "../include/hand.h"
#include "../include/card.h"

void hand_add_card(Hand *hand, Card card) {
    hand->cards[hand->count++] = card;
}

int hand_total(const Hand *hand) {
    int total = 0;
    for (int i = 0; i < hand->count; i++)
        total += card_value(&hand->cards[i]);
    return total;
}

void hand_clear(Hand *hand) {
    for (int i = 0; i < hand->count; i++)
        hand->cards[i] = (Card){0};
    hand->count = 0;
}
