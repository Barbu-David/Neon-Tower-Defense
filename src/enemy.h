#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "constants.c"
#include <stdbool.h>

typedef struct ENEMY_TYPE {
	float speed, hit_points;
	char name[max_enemy_name_size];
	Texture2D texture;
	int prize, penalty;
}enemy_type;

typedef struct PATH {
	Vector2 waypoint_list[max_waypoints_number];
	int max_waypoint, current_waypoint;
}path;

typedef struct ENEMY {
	bool alive;
	Vector2 position;
	path enemy_path;
	enemy_type type;
}enemy;

enemy* enemy_init(path enemy_path, enemy_type type);
void enemy_move(enemy* current_enemy, int* money, int* lives);
void enemy_draw(enemy* current_enemy);
void enemy_update(enemy* current_enemy, int* money, int* lives);
void enemy_die(enemy* current_enemy, int* money);
void enemy_enter(enemy* current_enemy, int* money, int* lives);

#endif
