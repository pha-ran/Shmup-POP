#pragma once

#include "output.h"
#include "player.h"
#include "enemy.h"

void InitBullet(void);
void AddBullet(char type, char x, char y);
void MoveBullet(void);
void DamageBullet(void);
void DrawBullet(void);
