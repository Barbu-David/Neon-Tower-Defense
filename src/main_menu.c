#include "main_menu.h"
#include <stdlib.h>

main_menu* menu_load(char* menu_path, char* dir_path)
{	
	FILE* menu_file=fopen(menu_path,"r");
	main_menu* menu=malloc(sizeof(main_menu));
	char texture_path[max_string];

	fscanf(menu_file,"%d",&(menu->number_of_levels));
	fscanf(menu_file,"%f",&(menu->origin_x));
	fscanf(menu_file,"%f",&(menu->origin_y));
	fscanf(menu_file,"%f",&(menu->width));
	fscanf(menu_file,"%f",&(menu->height));
	fscanf(menu_file,"%s",texture_path);
	menu->menu_texture=LoadTexture(texture_path);
	
	char slots[menu->number_of_levels][max_string];

	for (int i = 0; i < menu->number_of_levels; i++) 
		snprintf(slots[i], max_string, "slot%d", i + 1);



	fclose(menu_file);	

	return menu;
}
