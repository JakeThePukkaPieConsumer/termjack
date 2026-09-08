#pragma once

typedef enum {
    INPUT_NONE,
    INPUT_HIT,
    INPUT_STAND,
    INPUT_PLAY_AGAIN,
    INPUT_MENU,
    INPUT_QUIT,
} InputAction;

InputAction input_process(int ch);
