#include "raylib.h"
#include "constants.c"
#include "enemy.h"
#include "enemy_manager.h"
#include <stdlib.h>
#include "towers.h"
#include "bullet_types.h"
#include "file_parser.h"
#include "stdbool.h"

int main(void)
{
	InitWindow(screen_width, screen_height, "Tower defense");
	SetTargetFPS(60);
	
		

	level* level1=get_level_from_file("./assets/levels/level1.data");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		play_level(level1);
		EndDrawing();
	}
	
	level_unload(level1);
	CloseWindow();

	return 0;
}

