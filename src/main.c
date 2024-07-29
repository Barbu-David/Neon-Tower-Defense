#include "raylib.h"
#include "constants.c"
#include "enemy.h"
#include "enemy_manager.h"
#include <stdlib.h>
#include "towers.h"
#include "bullet_types.h"
#include "file_parser.h"

int main(void)
{
	const int screen_width = 800;
	const int screen_height = 450;

	InitWindow(screen_width, screen_height, "Tower defense");
	SetTargetFPS(60);

	Texture2D background = LoadTexture("assets/level1.png");

	enemy_list* list=malloc(sizeof(enemy_list));
	list->next=NULL;

	wave wave1=wave_from_file("./assets/waves/wave1");;
	wave *waves_level1=malloc(sizeof(wave));
	waves_level1[0]=wave1;

	bullet new_bullet=normal_bullet_get();
	bullet no_bullet=no_bullet_get();
	bullet_list* bl=malloc(sizeof(bullet_list));
	bl->next=NULL;
	
	tower* empty_tower=malloc(sizeof(tower));
	tower* new_tower=malloc(sizeof(tower));
	empty_tower->position.x=330;
	empty_tower->position.y=200;
	empty_tower->bullet_type=no_bullet;
	empty_tower->texture=LoadTexture("assets/empty_tower.png");
	empty_tower->open_menu=false;
	new_tower->radius=200;
	new_tower->start_time=0;
	new_tower->shoot_delay=1;
	new_tower->bullet_type=new_bullet;

	empty_tower->radius=200;
	empty_tower->start_time=0;
	empty_tower->shoot_delay=1;

	empty_tower->active_bullets=bl;
	new_tower->texture=LoadTexture("assets/blue_tower.png");
	new_tower->open_menu=false;
	new_tower->ring_texture=LoadTexture("assets/tower_ring.png");	
	empty_tower->ring_texture=new_tower->ring_texture;
	empty_tower->cost=malloc(sizeof(int));
	empty_tower->cost[0]=100;
	empty_tower->upgrade_possibility=malloc(sizeof(tower));	
	empty_tower->upgrade_possibility[0]=new_tower;

	int *money=malloc(sizeof(int));
	*(money)=200;
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		
		DrawTexture(background,0,0,WHITE);
		tower_update(empty_tower,1, list, money);
		enemies_spawn(waves_level1, 1, list);
		
		EndDrawing();
	}

	UnloadTexture(background);
	UnloadTexture(new_tower->texture);
	UnloadTexture(new_bullet.texture);
	UnloadTexture(new_tower->ring_texture);
	CloseWindow();

	return 0;
}

