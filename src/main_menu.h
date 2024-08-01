#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "raylib.h"
#include "level_player.h"

typedef struct LEVEL_BOX {
	Rectangle box;
	level* selected_level;
	char box_text[max_string], key[max_string];
}level_box;

typedef struct MAIN_MENU {
	Texture2D menu_texture;
	level_box* boxes;
	int number_of_levels;
	float width, height, origin_x,origin_y;
}main_menu;

main_menu* menu_load(char* menu_path, char* dir_path);
void menu_unload(main_menu* menu);

#endif
