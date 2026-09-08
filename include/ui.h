#pragma once

void ui_init(void);
void ui_shutdown(void);
void ui_clear_frame(void);
void ui_refresh_frame(void);
void ui_wait_frame(int fps);
int ui_get_input(void);
