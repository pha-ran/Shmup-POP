#pragma once

#include "input.h"
#include "output.h"
#include "file.h"

void InitPlayerInfo(void);
void InitPlayer(char sprite, char x, char y);
bool IsPlayerAlive(void);
void MovePlayer(void);
void DrawPlayer(void);
