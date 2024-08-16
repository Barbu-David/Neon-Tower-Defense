#include"game_controller.h"
#include<stdlib.h>
#include"file_parser.h"

game_controller* game_load(char* menu_path)
{
	game_controller* game=malloc(sizeof(game_controller));

	main_menu* menu = menu_load(menu_path);
	game->menu=menu;
	game->should_close=false;
	game->playing=false;
	game->current_level=NULL;
	return game;
}

void game_unload(game_controller* controller)
{
	menu_unload(controller->menu);
	if(controller->playing) level_unload(controller->current_level);
	free(controller);
}

void game_play(game_controller* controller)
{	
	int i;

	Vector2 mousePosition={GetMouseX(),GetMouseY()};

	if(controller->playing) 
	{	
		play_level(controller->current_level);

		Rectangle opt1={screen_width/2-controller->current_level->pause_menu_texture.width/2,screen_height/2-controller->current_level->pause_menu_texture.height/2,controller->current_level->pause_menu_texture.width,controller->current_level->pause_menu_texture.height/2};
			Rectangle opt2={screen_width/2-controller->current_level->pause_menu_texture.width/2,screen_height/2,controller->current_level->pause_menu_texture.width,controller->current_level->pause_menu_texture.height/2};
		

		if((controller->current_level->paused) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&  (CheckCollisionPointRec(mousePosition,opt1))))
		{	
			controller->playing=false;
			level_unload(controller->current_level);
		}
		else if((controller->current_level->paused) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&  (CheckCollisionPointRec(mousePosition,opt2))))
		{	
			controller->should_close=true;
		}
	}
	else 
	{
		DrawTexture(controller->menu->menu_texture,0,0,WHITE);
		for(i=0;i<controller->menu->number_of_levels;i++)
		{
			DrawRectangleRec(controller->menu->boxes[i].box,BLACK);
			DrawText(controller->menu->boxes[i].box_text,controller->menu->boxes[i].box.x,controller->menu->boxes[i].box.y,16,WHITE);

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePosition,controller->menu->boxes[i].box))
			{	
				controller->current_level=get_level_from_file(controller->menu->boxes[i].selected_level_path);
				controller->playing=true;
			}

		}
	}
}
