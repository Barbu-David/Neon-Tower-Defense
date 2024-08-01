#include "main_menu.h"
#include <stdlib.h>
#include <string.h>

main_menu* menu_load(char* menu_path)
{	
	FILE* menu_file=fopen(menu_path,"r");
	
	if(menu_file==NULL) perror("Failed to open file");
	

	main_menu* menu=malloc(sizeof(main_menu));
	char path[max_string];
	fscanf(menu_file,"%d",&(menu->number_of_levels));
	fscanf(menu_file,"%f",&(menu->origin_x));
	fscanf(menu_file,"%f",&(menu->origin_y));
	fscanf(menu_file,"%f",&(menu->width));
	fscanf(menu_file,"%f",&(menu->height));
	fscanf(menu_file,"%f",&(menu->space));
	fscanf(menu_file,"%s",path);
	menu->menu_texture=LoadTexture(path);
	
	menu->boxes=malloc(sizeof(level_box)*menu->number_of_levels);
	
	for(int i=0; i<menu->number_of_levels;i++)
	{
		Rectangle rec = {menu->origin_x+menu->space*i+menu->width*i,menu->origin_y,menu->width,menu->height};
		fscanf(menu_file,"%s",menu->boxes[i].selected_level_path);
		char box_text[max_string];
		sprintf(box_text,"%d",i+1);
		strcpy(menu->boxes[i].box_text,box_text);
		menu->boxes[i].box=rec;
	}	
	
	fclose(menu_file);	
	return menu;
}

void menu_unload(main_menu *menu)
{
	free(menu->boxes);
	free(menu);
}
