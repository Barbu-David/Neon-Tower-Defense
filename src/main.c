#include "raylib.h"
#include "constants.c"
#include <stdlib.h>
#include "stdbool.h"
#include "game_controller.h"

int main(void)
{
	InitWindow(screen_width, screen_height, "Tower defense");
	SetTargetFPS(60);	
	game_controller* game=game_load("./assets/menu_file/menu");
	while (!WindowShouldClose() && !game->should_close)
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		game_play(game);
		EndDrawing();
	}
	
	game_unload(game);
	
	CloseWindow();

	return 0;
}

