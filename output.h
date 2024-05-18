#pragma once

#include <windows.h>
#include <stdio.h>

#define CONSOLE_WIDTH	120
#define CONSOLE_HEIGHT	29

void InitConsole(void);
void MoveCursor(SHORT x, SHORT y);
void ClearBuffer(void);
void PrintBuffer(void);
void DrawSprite(SHORT x, SHORT y, CHAR sprite);
void DrawString(SHORT x, SHORT y, LPCSTR string);
