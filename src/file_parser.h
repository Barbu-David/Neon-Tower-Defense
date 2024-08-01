#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include"enemy_manager.h"
#include"towers.h"
#include<stdio.h>
#include<stdbool.h>

typedef struct LEVEL {
	Texture2D background, gui_texture, pause_menu_texture;
	int tower_number, waves_number;
	wave* wave_list;
	tower** tower_list;
	enemy_list* en_list;
	int* money;
	int* lives;
	double real_time, pause_time;
	bool paused;
	char* level_slot;
}level;

enemy_type enemy_type_from_file(char* enemy_file);
path path_from_file(char* path_file);
wave* wave_from_file(char* wave_file);
tower_type tower_type_from_file(char* tower_type_path);
tower** tower_list_from_file(char* tower_list_path);
int number_of_items_from_list(char* items_list);

void play_level(level* current_level);
level* get_level_from_file(char* level_file);
void level_unload(level* current_level);

#endif
