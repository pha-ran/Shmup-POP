#pragma once

void InitPlayerInfo(void);
void InitPlayer(char sprite, char x, char y);
bool IsPlayerAlive(void);
void MovePlayer(void);
void FirePlayer(void);
bool IsPlayerHit(char x, char y);
void DrawPlayer(void);
