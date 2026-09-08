#pragma once

#include "card.h"

typedef enum {
    HAND_PLAYER,
    HAND_DEALER,
} HandOwner;

typedef struct {
    Card cards[10];
    int count;
    HandOwner owner;
} Hand;

void hand_add_card(Hand *hand, Card card);
int hand_total(const Hand *hand);
void hand_clear(Hand *hand);
