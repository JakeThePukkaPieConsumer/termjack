#include "../include/card.h"
#include <ncurses.h>
#include <stdio.h>

const char *suit_names[] = {"Hearts", "Diamonds", "Spades", "Clubs"};
const char *rank_names[] = {
    "", "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King",
};

int card_value(const Card *card) {
    int ace = 1;
    int face = 10;

    if (card->rank == ace)
        return 11;
    if (card->rank >= face)
        return 10;

    return card->rank;
}

void card_draw(const Card *card, int row, int col) {
    int color_pair = (card->suit == HEARTS || card->suit == DIAMONDS) ? 2 : 1;

    attron(COLOR_PAIR(color_pair));
    mvprintw(x, y, "%s of %s", rank_names[card->rank], suit_names[card->suit]);
    attroff(COLOR_PAIR(color_pair));
}
