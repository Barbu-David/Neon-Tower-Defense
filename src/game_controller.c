#include"game_controller.h"
#include<stdlib.h>

game_controller* game_load(char* menu_path)
{
	game_controller* game=malloc(sizeof(game_controller));
	
	main_menu* menu = menu_load(menu_path);
	game->menu=menu;
	game->playing=false;
	game->current_level=malloc(sizeof(level));

	return game;
}

void game_unload(game_controller* controller)
{
	free(controller->current_level);
	menu_unload(controller->menu);
}
