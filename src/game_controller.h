#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include"main_menu.h"
#include<stdbool.h>

typedef struct GAME_CONTROLLER {
	bool playing;
	level* current_level;
	main_menu* menu;	
}game_controller;

void game_play(game_controller* controller);
void game_unload(game_controller* controller);
game_controller* game_load(char* dir_path, char* menu_path);
#endif
