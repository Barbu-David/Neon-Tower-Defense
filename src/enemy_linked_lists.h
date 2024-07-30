#ifndef ENEMY_CODE_LISTS_H
#define ENEMY_CODE_LISTS_H

#include "enemy.h"

typedef struct ENEMY_LIST{
    enemy* selected_enemy;
    struct ENEMY_LIST *next;
}enemy_list;

void push_enemy_to_list(enemy_list *head , enemy* new_element_value);
int return_no_enemy_list(enemy_list *head);
void update_enemy_list(enemy_list *head, int* money, int* lives);
enemy* enemy_in_range(Vector2 position, float radius,enemy_list* heada;
void unload_enemies(enemy_list *head);

#endif
