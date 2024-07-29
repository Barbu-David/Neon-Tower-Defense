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


	level* level1=get_level_from_file("./assets/levels/level1.data");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		
		play_level(level1);
			
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

