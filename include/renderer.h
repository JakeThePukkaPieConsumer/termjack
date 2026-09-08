#pragma once

#include "./game.h"
#include "./hand.h"
#include "./state.h"

void renderer_init(void);
void renderer_shutdown(void);

void renderer_clear(void);
void renderer_refresh(void);

void renderer_draw_player_hand(const Hand *player);
void renderer_draw_dealer_hand(const Hand *dealer, int show_hidden);
void renderer_draw_status_message(const char *message);
void renderer_draw_prompt(const char *prompt);
void renderer_draw_totals(int player_total, int dealer_total);

void renderer_draw_game_state(const Hand *player, const Hand *dealer, GameState state);
void renderer_draw_round_result(const RoundOutcome *outcome, int player_total, int dealer_total);
void renderer_draw_menu(void);
