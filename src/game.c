#include "../include/game.h"
#include "../include/deck.h"
#include "../include/input.h"
#include "../include/renderer.h"
#include "../include/state.h"
#include "../include/ui.h"

#define FPS 60

void game_run(void) {
    renderer_init();

    GameSession *session = game_session_create();
    Deck deck;

    int running = 1;
    int in_round = 0;

    while (running) {
        renderer_clear();
        int ch = ui_get_input();
        InputAction action = input_process(ch);

        if (action == INPUT_QUIT) {
            running = 0;
            continue;
        }

        switch (game_session_get_state(session)) {
            case STATE_START:
                if (action == INPUT_PLAY_AGAIN || action == INPUT_MENU) {
                    game_session_start_round(session, &deck);
                    in_round = 1;
                }
                break;

            case STATE_PLAYER_TURN:
                if (action == INPUT_HIT) {
                    game_session_player_hit(session, &deck);
                }
                if (action == INPUT_STAND) {
                    game_session_player_stand(session);
                }
                break;

            case STATE_DEALER_TURN:
                game_session_dealer_turn(session, &deck);
                break;

            case STATE_ROUND_OVER: {
                if (action == INPUT_PLAY_AGAIN) {
                    game_session_start_round(session, &deck);
                } else if (action == INPUT_MENU || action == INPUT_QUIT) {
                    in_round = 0;
                    game_session_set_state(session, STATE_START);
                }
                break;
            }

            case STATE_MENU:
            default:
                break;
        }

        if (!in_round || game_session_get_state(session) == STATE_START) {
            renderer_draw_menu();
        } else {
            renderer_draw_game_state(game_session_get_player_hand(session),
                                     game_session_get_dealer_hand(session),
                                     game_session_get_state(session));

            if (game_session_get_state(session) == STATE_ROUND_OVER) {
                RoundOutcome outcome = game_session_evaluate(session);
                renderer_draw_round_result(&outcome, game_session_player_total(session),
                                           game_session_dealer_total(session));
            }
        }

        renderer_refresh();
        ui_wait_frame(FPS);
    }

    game_session_destroy(session);
    renderer_shutdown();
}
