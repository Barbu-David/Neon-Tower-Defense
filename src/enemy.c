#include "raylib.h"
#include "enemy.h"
#include "constants.c"
#include "stdlib.h"
#include "math.h"
#include <stdbool.h>

enemy* enemy_init(path enemy_path, enemy_type type)
{
	enemy* current_enemy=malloc(sizeof(enemy));
	current_enemy->type=type;
	current_enemy->position=enemy_path.waypoint_list[0];
	current_enemy->enemy_path=enemy_path;
	current_enemy->alive=true;
	return current_enemy;
}

void enemy_enter(enemy* current_enemy, int* money, int* lives)
{
	*(lives)-=current_enemy->type.penalty;
	enemy_die(current_enemy, money);
}

void enemy_die(enemy* current_enemy, int* money)
{	
	*(money)+=current_enemy->type.prize;	
	current_enemy->alive=false;
}

void enemy_move(enemy* current_enemy, int* money, int* lives)
{	

	float currentX=current_enemy->position.x;
	float currentY=current_enemy->position.y;
	float targetX=current_enemy->enemy_path.waypoint_list[current_enemy->enemy_path.current_waypoint+1].x;
	float targetY=current_enemy->enemy_path.waypoint_list[current_enemy->enemy_path.current_waypoint+1].y;
	float frame_time=GetFrameTime();
	float speed=current_enemy->type.speed*frame_time;

	float directionX = targetX - currentX;
	float directionY = targetY - currentY;

	float distance = sqrt(directionX * directionX + directionY * directionY);
		
	if (distance < speed) {
		current_enemy->enemy_path.current_waypoint++;
		if(current_enemy->enemy_path.current_waypoint>=current_enemy->enemy_path.max_waypoint-1)
		{
		enemy_enter(current_enemy, money, lives);
		}
	}
	else {
		directionX /= distance;
		directionY /= distance;

		directionX *= speed;
		directionY *= speed;

		current_enemy->position.x += directionX;
		current_enemy->position.y += directionY;

	}

}

void enemy_draw(enemy* current_enemy)
{
	DrawTexture(current_enemy->type.texture, current_enemy->position.x,current_enemy->position.y, WHITE);
}

void enemy_update(enemy* current_enemy, int* money, int* lives)
{	
	enemy_draw(current_enemy);
	enemy_move(current_enemy,  money,  lives);
	if(current_enemy->type.hit_points<=0) enemy_die(current_enemy,money);
}

