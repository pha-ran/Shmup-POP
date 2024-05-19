#pragma once

#include "input.h"
#include "output.h"
#include "file.h"
#include "bullet.h"

void InitPlayerInfo(void);
void InitPlayer(char sprite, char x, char y);
bool IsPlayerAlive(void);
void MovePlayer(void);
void FirePlayer(void);
void DrawPlayer(void);
