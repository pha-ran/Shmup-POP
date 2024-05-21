#pragma once

#define CONSOLE_WIDTH	(120)
#define CONSOLE_HEIGHT	(29)

void InitConsole(void);
void MoveCursor(short x, short y);
void ClearBuffer(void);
void PrintBuffer(void);
void DrawSprite(short x, short y, char sprite);
void DrawString(short x, short y, const char* string);
void ClearHUD(void);
