#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include"main_menu.h"

typedef struct GAME_CONTROLLER {
	level* current_level;
	main_menu* menu;	
}game_controller;

void game_play(game_controller* controller);


#endif
