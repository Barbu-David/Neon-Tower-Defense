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
		perror("Failed to open file lmao");
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
	printf("Line 34");
	for(i=0;i<strlen(name);i++) new_type.name[i]=name[i];
	new_type.name[i+1]='\0';

	new_type.texture=LoadTexture(texture_path);	

	return new_type;

}

level* get_level_from_file(FILE* level_file)
{
	level* new_level;

	return new_level;	

}

void play_level(level* current_level)
{

}
