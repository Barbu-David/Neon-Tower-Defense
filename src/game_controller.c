#include"game_controller.h"
#include<stdlib.h>

game_controller* game_load(char* dir_path, char* menu_path)
{
	game_controller* game=malloc(sizeof(game_controller));
	
	main_menu* menu = menu_load(menu_path, dir_path);
	game->menu=menu;
	game->playing=false;
	game->current_level=NULL;

	return game;
}
