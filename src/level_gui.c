#include"level_gui.h"
#include"constants.c"

void draw_level_gui(level* current_level)
{
	char gui_text[gui_string_buffer_size];
	sprintf(gui_text,"Money: %d Lives: %d",*(current_level->money),*(current_level->lives));
	DrawText(gui_text,gui_position_x,gui_position_y,gui_text_size,BLACK);
}
