#include "./include/game.h"
#include "./include/ui.h"
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand(time(NULL));

    ui_init();
    game_run();
    ui_shutdown();

    return 0;
}
