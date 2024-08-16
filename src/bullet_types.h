#ifndef BULLET_TYPES_H
#define BULLET_TYPES_H

#include"towers.h"

void normal_bullet_move(bullet* current_bullet, int damage, float speed);
bullet normal_bullet_get();
void no_bullet_move(bullet* current_bullet, int damage, float speed);
bullet no_bullet_get();
bullet get_bullet(int type);
#endif
