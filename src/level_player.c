#include "level_player.h"
#include <stdlib.h>

void level_pause(level* current_level)
{
	if(IsKeyPressed(KEY_P)) 
	{
		if((current_level->paused))	
		{
			current_level->pause_time+=GetTime();
		}
		else current_level->pause_time-=GetTime();
		current_level->paused=!(current_level->paused);
	}	
}

void play_level(level* current_level)
{	
	DrawTexture(current_level->background,0,0,WHITE);
	draw_level_gui(current_level);
	level_pause(current_level);
	if(!current_level->paused)
	{
		enemies_spawn(current_level->wave_list,current_level->waves_number,current_level->en_list,current_level->real_time,current_level->pause_time,current_level->money,current_level->lives);

		tower_update(current_level->tower_list,current_level->tower_number,current_level->en_list,current_level->money);
	}

}

void level_unload(level* current_level)
{
	free(current_level->money);
	free(current_level->lives);
	UnloadTexture(current_level->background);    
	unload_towers(current_level->tower_list,current_level->tower_number);
	unload_enemies(current_level->en_list);
	free(current_level->wave_list);
	free(current_level); 
}

