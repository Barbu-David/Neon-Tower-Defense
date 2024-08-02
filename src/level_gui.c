#include"level_gui.h"
#include"constants.c"

void draw_level_gui(level* current_level)
{	
	char gui_text[max_string];
	DrawTexture(current_level->gui_texture,0,0,WHITE);
	sprintf(gui_text," %d",*(current_level->lives));
	DrawText(gui_text,70, 5,gui_text_size,BLACK);
	sprintf(gui_text," %d",*(current_level->money));
	DrawText(gui_text,70 ,40,gui_text_size,BLACK);
}

void menu_gui_update(level* current_level)
{
        DrawTexture(current_level->pause_menu_texture,screen_width/2-current_level->pause_menu_texture.width/2,screen_height/2-current_level->pause_menu_texture.height/2,WHITE);
        DrawText("Main menu",20+screen_width/2-current_level->pause_menu_texture.width/2,screen_height/2-current_level->pause_menu_texture.height/2,gui_text_size,BLACK);
        DrawText("Exit",20+screen_width/2-current_level->pause_menu_texture.width/2,screen_height/2,gui_text_size,BLACK);
}

