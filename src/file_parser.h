#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include"level_player.h"

enemy_type enemy_type_from_file(char* enemy_file);
path path_from_file(char* path_file);
wave* wave_from_file(char* wave_file);
tower_type tower_type_from_file(char* tower_type_path);
tower** tower_list_from_file(char* tower_list_path);
int number_of_items_from_list(char* items_list);
level* get_level_from_file(char* level_file);

#endif
