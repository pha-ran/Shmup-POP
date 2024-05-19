#pragma once

#include "input.h"
#include "output.h"
#include "file.h"

void InitEnemyInfo(void);
void InitEnemy(void);
void AddEnemy(char sprite, char x, char y);
bool IsEnemyAlive(void);
void MoveEnemy(void);
void DrawEnemy(void);
