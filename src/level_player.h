#ifndef LEVEL_PLAYER_H
#define LEVEL_PLAYER_H

#include"enemy_manager.h"
#include"towers.h"
#include<stdio.h>
#include<stdbool.h>

typedef struct LEVEL {
        Texture2D background, gui_texture, pause_menu_texture;
        int tower_number, waves_number;
        wave* wave_list;
        tower** tower_list;
        enemy_list* en_list;
        int* money;
        int* lives;
        double real_time, pause_time;
        bool paused;
}level;




void level_pause(level* current_level);
void play_level(level* current_level);
void level_unload(level* current_level);


#endif
