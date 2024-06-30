#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "enemy.h"
#include "linked_lists.h"

typedef struct WAVE_ITEM {
	int enemy_quantity, selected_subpath;
	double spawn_delay;
	enemy_type type;
}wave_item;

typedef struct WAVE {
	double start_time, elapsed_time;
	wave_item item[max_wave_item];
	path subpaths[max_subpaths];
	int wave_item_number;
}wave;

void enemies_spawn(wave *level_waves, int wave_number, enemy_list* active_enemies);

#endif
