#include "enemy_manager.h"
#include <stdlib.h>
#include "enemy_linked_lists.h"

void enemies_spawn (wave *level_waves, int wave_number, enemy_list* active_enemies)
{
	double current_time=GetTime();
	int wave_index, wave_item_index;

	for(wave_index=0; wave_index<wave_number; wave_index++)
	{	
		if(level_waves[wave_index].start_time<current_time)
		{	
			level_waves[wave_index].elapsed_time=current_time-level_waves[wave_index].start_time;

			for(wave_item_index=0;wave_item_index<level_waves[wave_index].wave_item_number;wave_item_index++)
			{	
				if(level_waves[wave_index].item[wave_item_index].enemy_quantity>0 && level_waves[wave_index].item[wave_item_index].spawn_delay<level_waves[wave_index].elapsed_time)
				{	
					enemy* new_enemy=enemy_init(level_waves[wave_index].subpaths[level_waves[wave_index].item[wave_item_index].selected_subpath], level_waves[wave_index].item[wave_item_index].type);
					push_enemy_to_list(active_enemies, new_enemy);
					level_waves[wave_index].start_time=current_time;	
					level_waves[wave_index].item[wave_item_index].enemy_quantity--;
				}

			}
		}
	}

	update_enemy_list(active_enemies);

}
