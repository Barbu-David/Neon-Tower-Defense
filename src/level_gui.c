#include"level_gui.h"
#include"constants.c"

void draw_level_gui(level* current_level)
{	
	Texture2D text=LoadTexture("./assets/tower_textures/level_gui.png");
	char gui_text[max_string];
	DrawTexture(text,0,0,WHITE);
	sprintf(gui_text," %d",*(current_level->lives));
	DrawText(gui_text,70, 5,gui_text_size,BLACK);
	sprintf(gui_text," %d",*(current_level->money));
	DrawText(gui_text,70 ,40,gui_text_size,BLACK);
}
