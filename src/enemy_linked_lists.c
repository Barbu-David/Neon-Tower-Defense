#include <stdlib.h>
#include "enemy.h"
#include "enemy_linked_lists.h"
#include "math.h"
#include <stdbool.h>

void push_enemy_to_list(enemy_list *head, enemy* new_element_value){
	enemy_list *new_element = malloc(sizeof(enemy_list));
	enemy_list *iterator = head;
	enemy_list *last_element;
	
	while (iterator->next != NULL) {
		iterator = iterator->next;
	}
	last_element = iterator;

	last_element->next = new_element;
	new_element->selected_enemy = new_element_value;
	new_element->next = NULL;
}

void update_enemy_list(enemy_list *head, int* money, int* lives){
	enemy_list *iterator = head->next;  
	enemy_list *previous = head;        

	while (iterator != NULL){
		enemy_list *next = iterator->next;

		enemy_update(iterator->selected_enemy, money, lives);

		if (!iterator->selected_enemy->alive) {
			previous->next = next;
			free(iterator->selected_enemy);
			free(iterator);
		}
		else {
			previous = iterator;
		}

		iterator = next;
	}
}

int return_no_enemy_list(enemy_list *head){
	int no_elements ;
	enemy_list *iterator;
	iterator = head;
	no_elements = 0;

	while (iterator->next != NULL){
		no_elements++;
		iterator = iterator->next;
	}

	return no_elements;
}

enemy* enemy_in_range(Vector2 position, float radius,enemy_list *head){
	enemy_list *iterator = head->next;  
	bool found=false;
	enemy* target;
	
	while (iterator != NULL){
		enemy_list *next = iterator->next;
		
		float distanceX=iterator->selected_enemy->position.x-position.x;
		float distanceY=iterator->selected_enemy->position.y-position.y;
		float distance=sqrt(distanceX*distanceX+distanceY*distanceY);	

		if (distance<radius) 
		{
			target=iterator->selected_enemy;
			radius=distance;
			found=true;
		}
		iterator = next;
	}
	if(found) return target;
	return NULL;
}

void unload_enemies(enemy_list* head)
{
	enemy_list *iterator = head->next;  
	while (iterator != NULL){
		enemy_list *next = iterator->next;
		free(iterator->selected_enemy);
		free(iterator);
		iterator = next;
	}

	free(head);

}
