#include"file_parser.h"
#include<stdio.h>
#include<string.h>
#include"constants.c"
#include<stdlib.h>

enemy_type enemy_type_from_file(char* enemy_file)
{	
	unsigned int i;

	FILE* file = fopen(enemy_file,"r");
	if (file == NULL) {
		perror("Failed to open file ");
	}

	float speed, hit_points;
	char* name = malloc(sizeof(char)*max_enemy_name_size);
	char trash[max_string];
	char texture_path[max_string];

	fscanf(file,"%s",trash);
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
	for(i=0;i<strlen(name);i++) new_type.name[i]=name[i];
	new_type.name[i+1]='\0';

	new_type.texture=LoadTexture(texture_path);	

	return new_type;

}

path path_from_file(char* path_file)
{	
	int i;
	path new_path;
	FILE* file=fopen(path_file,"r");
	if (file == NULL) {
		perror("Failed to open file ");
	}

	fscanf(file,"%d",&new_path.current_waypoint);
	fscanf(file,"%d",&new_path.max_waypoint);
	
	for(i=0;i<new_path.max_waypoint;i++)
	{
		fscanf(file, "%f", &new_path.waypoint_list[i].x);
		fscanf(file, "%f", &new_path.waypoint_list[i].y);
	}	
	
	fclose(file);
	
	return new_path;
}

wave wave_from_file(char* wave_file)
{
	FILE* file=fopen(wave_file,"r");
	if (file == NULL) {
		perror("Failed to open file ");
	
	}
	
	char wave_path[max_string], enemy_type_path[max_string];
	wave new_wave;
	int number_of_paths, i;

	fscanf(file,"%lf", &new_wave.start_time);
	fscanf(file,"%d", &number_of_paths);
	
	for(i=0;i<number_of_paths;i++)
	{
	fscanf(file,"%s",wave_path);
	new_wave.subpaths[i]=path_from_file(wave_path);
	}

	fscanf(file,"%d",&new_wave.wave_item_number);
	
	for(i=0;i<new_wave.wave_item_number;i++)
	{
		wave_item new_item;
		fscanf(file,"%d",&new_item.enemy_quantity);
		fscanf(file,"%lf",&new_item.spawn_delay);
		fscanf(file,"%d",&new_item.selected_subpath);
		fscanf(file,"%s",enemy_type_path);
		new_item.type=enemy_type_from_file(enemy_type_path);
		
		new_wave.item[i]=new_item;
	}

	fclose(file);
	return new_wave;
}

/*
level* get_level_from_file(FILE* level_file)
{
	level* new_level;

	return new_level;	

}

void play_level(level* current_level)
{

}*/
