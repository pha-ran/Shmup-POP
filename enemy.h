#pragma once

void InitEnemyInfo(void);
void InitEnemy(void);
void AddEnemy(char sprite, char x, char y);
bool IsEnemyAlive(void);
void MoveEnemy(void);
void FireEnemy(void);
bool IsEnemyHit(char x, char y);
void DrawEnemy(void);
