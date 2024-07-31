#ifndef TOWERS_H
#define TOWERS_H

#include"raylib.h"
#include<stdbool.h>
#include"enemy_linked_lists.h"

typedef struct BULLET{
	Vector2 position;
	enemy* target;
	Texture2D texture;
	void (*bullet_move) (struct BULLET*);
	bool active;
}bullet;

typedef struct BULLET_LIST{
	bullet* selected_bullet;
	struct BULLET_LIST *next;
}bullet_list;

typedef struct TOWER_TYPE{
	Texture2D texture, ring_texture;
	float radius;
	int upgrade_options_number;
	struct TOWER_TYPE* upgrade_possibility;
	int cost;
	double shoot_delay;
	bullet bullet_type;
}tower_type;

typedef struct TOWER{
	Vector2 position;
	double start_time, elapsed_time;
	bool open_menu;
	bullet_list* active_bullets;
	tower_type type;
}tower;

bullet* bullet_init(Vector2 position, enemy* target, Texture2D texture, void(*bullet_move)(bullet*) );
void bullet_draw(bullet* current_bullet);
void bullet_update(bullet* current_bullet, enemy_list* list, float radius);
void tower_shoot(tower* current_tower,enemy_list* list, float time_offset);
void tower_click(tower* current_tower, int* total_money);
void tower_draw(tower* current_tower);
void tower_update(tower** current_tower_list, int number_of_towers, enemy_list* list, int* total_money, float time_offset);
void push_bullet_to_list(bullet_list *head , bullet* new_element_value);
void update_bullet_list(bullet_list *head, enemy_list* list, float radius);
void tower_upgrade(tower* current_tower, int upgrade_number, int* total_money);
void unload_towers(tower** tower_list, int number_of_towers);
void bullet_find_target(bullet* current_bulet, enemy_list* list, float radius);

#endif
