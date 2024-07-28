#include"file_parser.h"
#include<stdio.h>
#include<string.h>
#include"constants.c"

enemy_type enemy_type_from_file(char* enemy_file)
{
	FILE* file = fopen("r",enemy_file);
	float speed, hit_points;
	char* name = malloc(sizeof(char)*max_enemy_name_size);
	char[100] trash;
	char[100] texture_path;

	fscanf(file,"%s",name);

	fscanf(file,"%s",trash);
	fscanf(file,"%s",texture_path);	

	fscanf(file,"%s",trash);
	fscanf(file,"%f",&speed);

	fscanf(file,"%s",trash);
	fscanf(file,"%f",&hit_points);

	fclose(file);

	enemy_type new_type;
	new_type.speed=speed;
	new_type.hit_points=hit_points;
//TO DO	
}

level* get_level_from_file(FILE* level_file)
{
	level* new_level;
	

}

void play_level(level* current_level)
{

}
