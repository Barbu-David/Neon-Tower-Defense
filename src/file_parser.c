#include"file_parser.h"
#include<stdio.h>
#include<string.h>
#include"constants.c"
#include<stdlib.h>
#include"bullet_types.h"

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

wave* wave_from_file(char* wave_file)
{
	FILE* file=fopen(wave_file,"r");
	if (file == NULL) {
		perror("Failed to open file ");

	}
	int n,j;
	fscanf(file,"%d",&n);
	wave* wave_list=malloc(sizeof(wave)*n);

	char wave_path[max_string], enemy_type_path[max_string];

	for(j=0;j<n;j++)
	{
		int number_of_paths, i;

		fscanf(file,"%lf", &wave_list[j].start_time);
		fscanf(file,"%d", &number_of_paths);

		for(i=0;i<number_of_paths;i++)
		{
			fscanf(file,"%s",wave_path);
			wave_list[j].subpaths[i]=path_from_file(wave_path);
		}

		fscanf(file,"%d",&wave_list[j].wave_item_number);

		for(i=0;i<wave_list[j].wave_item_number;i++)
		{
			wave_item new_item;
			fscanf(file,"%d",&new_item.enemy_quantity);
			fscanf(file,"%lf",&new_item.spawn_delay);
			fscanf(file,"%d",&new_item.selected_subpath);
			fscanf(file,"%s",enemy_type_path);
			new_item.type=enemy_type_from_file(enemy_type_path);

			wave_list[j].item[i]=new_item;
		}

	}
	fclose(file);
	return wave_list;
}

tower_type tower_type_from_file(char* tower_type_path)
{
	FILE* file=fopen(tower_type_path,"r");
	if (file == NULL) {
		perror("1Failed to open file ");
	}
	tower_type new_type;
	int bullet_type, i;
	char tower_texture_path[max_string], ring_texture_path[max_string];

	fscanf(file,"%d",&bullet_type);
	fscanf(file,"%s",tower_texture_path);
	fscanf(file,"%s",ring_texture_path);
	fscanf(file,"%d",&new_type.cost);
	fscanf(file,"%lf",&new_type.shoot_delay);
	fscanf(file,"%f",&new_type.radius);
	fscanf(file,"%d",&new_type.upgrade_options_number);
	new_type.texture=LoadTexture(tower_texture_path);
	new_type.ring_texture=LoadTexture(ring_texture_path);
	new_type.bullet_type=get_bullet(bullet_type);

	new_type.upgrade_possibility=malloc(sizeof(tower_type)*new_type.upgrade_options_number);

	for(i=0;i<new_type.upgrade_options_number;i++)
	{	
		char upgrade_path[max_string];
		fscanf(file,"%s",upgrade_path);
		new_type.upgrade_possibility[i]=tower_type_from_file(upgrade_path);
	}

	fclose(file);
	return new_type;
}

int number_of_items_from_list(char* items_list)
{
	int n;
	FILE* file=fopen(items_list,"r");
	if (file == NULL) {
		perror("Failed to open file ");
	}
	fscanf(file,"%d",&n);
	fclose(file);	
	return n;			
}

tower** tower_list_from_file(char* tower_list_path)
{
	int n,i;
	FILE* file=fopen(tower_list_path,"r");
	if (file == NULL) {
		perror("Failed to open file ");
	}
	fscanf(file,"%d",&n);
	tower** tower_list=malloc(sizeof(tower*)*n);	

	for(i=0;i<n;i++)
	{
		tower_list[i]=malloc(sizeof(tower));
		bullet_list* bl=malloc(sizeof(bullet_list));
		bl->next=NULL;
		char type_path[max_string];

		fscanf(file,"%f",&tower_list[i]->position.x);
		fscanf(file,"%f",&tower_list[i]->position.y);
		fscanf(file,"%s",type_path);

		tower_list[i]->type=tower_type_from_file(type_path);
		tower_list[i]->open_menu=false;
		tower_list[i]->active_bullets=bl;
		tower_list[i]->start_time=0;
	}

	fclose(file);	
	return tower_list;
}

level* get_level_from_file(char* level_file)
{

	level* new_level=malloc(sizeof(level));
	FILE* file=fopen(level_file,"r");
	if (file == NULL) {
		perror("Failed to open file ");
	}
	char back_path[max_string], wave_path[max_string], towers_path[max_string];

	new_level->lives=malloc(sizeof(int));
	new_level->money=malloc(sizeof(int));
	fscanf(file,"%d",new_level->money);
	fscanf(file,"%d",new_level->lives);	


	fscanf(file,"%s",back_path);
	fscanf(file,"%s",wave_path);

	fscanf(file,"%s",towers_path);
	new_level->tower_number=number_of_items_from_list(towers_path);
	new_level->waves_number=number_of_items_from_list(wave_path);
	new_level->wave_list=wave_from_file(wave_path);
	new_level->tower_list=tower_list_from_file(towers_path);
	new_level->background=LoadTexture(back_path);
	enemy_list* list=malloc(sizeof(enemy_list));
	list->next=NULL;
	new_level->en_list=list;

	fclose(file);
	return new_level;	
}

void play_level(level* current_level)
{
	DrawTexture(current_level->background,0,0,WHITE);

	enemies_spawn(current_level->wave_list,current_level->waves_number,current_level->en_list);

	tower_update(current_level->tower_list,current_level->tower_number,current_level->en_list,current_level->money);

}

void level_unload(level* current_level)
{
	free(current_level->money);
	free(current_level->lives);
	UnloadTexture(current_level->background);	
	unload_towers(current_level->tower_list,current_level->tower_number);
	unload_enemies(current_level->en_list);
	free(current_level->wave_list);
}
