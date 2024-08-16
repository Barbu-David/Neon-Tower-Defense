#include"raylib.h"
#include"towers.h"
#include<stdlib.h>
#include<math.h>
#include"constants.c"

int upgrade_options_select(tower* current_tower, Vector2 mousePosition)
{	

	if (current_tower->type.upgrade_options_number>0 &&
			mousePosition.x >= current_tower->position.x -current_tower->type.texture.width/2 &&
			mousePosition.x <= current_tower->position.x -current_tower->type.texture.width/2 + option_width &&
			mousePosition.y >= current_tower->position.y -current_tower->type.texture.height/2 &&
			mousePosition.y <= current_tower->position.y -current_tower->type.texture.height/2+ option_height) return 0;

	if (current_tower->type.upgrade_options_number>1 &&
			mousePosition.x >= current_tower->position.x +current_tower->type.texture.width &&
			mousePosition.x <= current_tower->position.x +current_tower->type.texture.width + option_width &&
			mousePosition.y >= current_tower->position.y -current_tower->type.texture.height/2 &&
			mousePosition.y <= current_tower->position.y -current_tower->type.texture.height/2+ option_height) return 1;

	if (current_tower->type.upgrade_options_number>2 &&
			mousePosition.x >= current_tower->position.x -current_tower->type.texture.width/2 &&
			mousePosition.x <= current_tower->position.x -current_tower->type.texture.width/2 + option_width &&
			mousePosition.y >= current_tower->position.y +current_tower->type.texture.height/2 &&
			mousePosition.y <= current_tower->position.y +current_tower->type.texture.height/2+ option_height) return 2;

	if (current_tower->type.upgrade_options_number>3 &&
			mousePosition.x >= current_tower->position.x +current_tower->type.texture.width &&
			mousePosition.x <= current_tower->position.x +current_tower->type.texture.width + option_width &&
			mousePosition.y >= current_tower->position.y +current_tower->type.texture.height/2 &&
			mousePosition.y <= current_tower->position.y +current_tower->type.texture.height/2+ option_height) return 3;

	return FAIL;
}

void push_bullet_to_list(bullet_list *head, bullet* new_element_value){
	bullet_list *new_element = malloc(sizeof(bullet_list));
	bullet_list *iterator = head;
	bullet_list *last_element;

	while (iterator->next != NULL) {
		iterator = iterator->next;
	}
	last_element = iterator;

	last_element->next = new_element;
	new_element->selected_bullet = new_element_value;
	new_element->next = NULL;
}

bullet* bullet_init(Vector2 position, enemy* target, Texture2D texture, void(*bullet_move)(bullet*, int, float))
{
	bullet* new_bullet=malloc(sizeof(bullet));
	new_bullet->position=position;
	new_bullet->target=target;
	new_bullet->texture=texture;
	new_bullet->bullet_move=bullet_move;
	new_bullet->active=true;
	return new_bullet;
}

void bullet_find_target(bullet* current_bullet, enemy_list* list, float radius)
{	
	enemy* enemy_to_shoot=enemy_in_range(current_bullet->position,radius,list);

	if(enemy_to_shoot==NULL) current_bullet->target=NULL;
	else current_bullet->target=enemy_to_shoot;
}

void bullet_draw(bullet* current_bullet)
{
	DrawTexture(current_bullet->texture, current_bullet->position.x,current_bullet->position.y, WHITE);
}

void bullet_update(bullet* current_bullet, enemy_list* list, float radius, int damage, float speed)
{
	bullet_find_target(current_bullet, list, radius);
	bullet_draw(current_bullet);
	current_bullet->bullet_move(current_bullet,damage, speed);
}


void update_bullet_list(bullet_list *head, enemy_list* list, float radius, int damage, float speed){
	bullet_list *iterator = head->next;
	bullet_list *previous = head;

	while (iterator != NULL){
		bullet_list *next = iterator->next;

		bullet_update(iterator->selected_bullet, list, radius, damage, speed);

		if (!iterator->selected_bullet->active) {
			previous->next = next;
			free(iterator->selected_bullet);
			free(iterator);
		} else {
			previous = iterator;
		}

		iterator = next;
	}
}

void unload_bullet_list(bullet_list *head){
	bullet_list *iterator = head->next;

	while (iterator != NULL){
		bullet_list *next = iterator->next;
		free(iterator->selected_bullet);
		free(iterator);

		iterator = next;
	}

	free(head);
}


void tower_shoot(tower* current_tower, enemy_list* list, float time_offset){

	current_tower->elapsed_time=GetTime()-time_offset;
	Vector2 bullet_position={current_tower->position.x+current_tower->type.texture.width/2, current_tower->position.y+current_tower->type.texture.height/2};

	if(current_tower->type.bullet_type.active && current_tower->elapsed_time-current_tower->start_time>current_tower->type.shoot_delay)
	{
		enemy* enemy_to_shoot=enemy_in_range(bullet_position,current_tower->type.radius,list);
		if(enemy_to_shoot!=NULL)
		{	
			bullet* shot_bullet=bullet_init(bullet_position, enemy_to_shoot, current_tower->type.bullet_type.texture, current_tower->type.bullet_type.bullet_move);
			current_tower->start_time=current_tower->elapsed_time;
			push_bullet_to_list(current_tower->active_bullets,shot_bullet);
		}	
	}

	update_bullet_list(current_tower->active_bullets, list, current_tower->type.radius, current_tower->type.bullet_damage, current_tower->type.bullet_speed);

}

void tower_click(tower* current_tower, int* total_money){

	Vector2 mousePosition={GetMouseX(),GetMouseY()};

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && current_tower->open_menu==true )
	{	
		int option=upgrade_options_select(current_tower,mousePosition);
		if(option!=FAIL)
		{
			tower_upgrade(current_tower, option, total_money);
			current_tower->open_menu=false;
		}

	}

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		if (mousePosition.x >= current_tower->position.x && mousePosition.x <= current_tower->position.x + current_tower->type.texture.width && mousePosition.y >= current_tower->position.y && mousePosition.y <= current_tower->position.y + current_tower->type.texture.height) {
			current_tower->open_menu = !current_tower->open_menu; 
		}	else current_tower->open_menu =false;
	}


}	
void tower_draw(tower* current_tower){
	DrawCircleLines(current_tower->position.x+current_tower->type.texture.width/2,current_tower->position.y+current_tower->type.texture.height/2,current_tower->type.radius,WHITE);
	DrawTexture(current_tower->type.texture, current_tower->position.x,current_tower->position.y, WHITE);
	if(current_tower->open_menu) DrawTexture(current_tower->type.ring_texture, current_tower->position.x-current_tower->type.texture.width/2,current_tower->position.y-current_tower->type.texture.height/2, WHITE);

}

void tower_update(tower** current_tower_list, int number_of_towers, enemy_list* list, int* total_money, float time_offset)
{
	for(int i=0;i<number_of_towers;i++)
	{
		tower_shoot(current_tower_list[i], list, time_offset);
		tower_click(current_tower_list[i], total_money);
		tower_draw(current_tower_list[i]);
	}
}

void free_tower_type(tower_type* type) {

	if (type->upgrade_possibility != NULL) {
		for (int i = 0; i < type->upgrade_options_number; ++i) {
			free_tower_type(&(type->upgrade_possibility[i]));
		}
		free(type->upgrade_possibility);
		type->upgrade_possibility = NULL;
	}
}


void tower_upgrade(tower* current_tower, int upgrade_number, int* total_money ){	
	if(*(total_money)>=current_tower->type.upgrade_possibility[upgrade_number].cost)
	{
		*(total_money)-=current_tower->type.upgrade_possibility[upgrade_number].cost;
		tower_type upgrade=current_tower->type.upgrade_possibility[upgrade_number];
		free_tower_type(&(current_tower->type));
		current_tower->type=upgrade;
	}
}

void unload_towers(tower** tower_list, int number_of_towers)
{
	for(int i=0;i<number_of_towers;i++)
	{
		UnloadTexture(tower_list[i]->type.texture);
		UnloadTexture(tower_list[i]->type.ring_texture);
		unload_bullet_list(tower_list[i]->active_bullets);
		free_tower_type(&(tower_list[i]->type));
		free(tower_list[i]);
	}

	free(tower_list);
}
