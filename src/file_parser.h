#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include"enemy_manager.h"
#include"towers.h"
#include<stdio.h>

typedef struct LEVEL {
	int path_number, enemy_type_number, tower_number, wave_number;
	int *money, *lives, *wave_item_number;
	double start_time;
	wave_item* wave_items;
	enemy_type* all_enemy_types;
	enemy_list* all_enemey_list;
	tower** tower_list;
	wave* wave;
}level;

enemy_type enemy_type_from_file(char* enemy_file);
path path_from_file(char* path_file);
wave wave_from_file(char* wave_file);

void play_level(level* current_level);
level* get_level_from_file(FILE* level_file);

#endif
