#include "output.h"
#include <stdio.h>
#include <windows.h>

#define	BUFFER_WIDTH	(CONSOLE_WIDTH + 1)
#define	BUFFER_HEIGHT	(CONSOLE_HEIGHT)

static HANDLE console;
static char buffer[BUFFER_HEIGHT][BUFFER_WIDTH];
static char blankLine[BUFFER_WIDTH];

void InitConsole(void)
{
	CONSOLE_CURSOR_INFO cursor;
	SHORT index;

	console = GetStdHandle(STD_OUTPUT_HANDLE);

	cursor.bVisible = FALSE;
	cursor.dwSize = 1;

	SetConsoleCursorInfo(console, &cursor);

	for (index = 0; index < BUFFER_WIDTH - 1; ++index)
		blankLine[index] = ' ';

	blankLine[BUFFER_WIDTH - 2] = '\0';
}

void MoveCursor(short x, short y)
{
	COORD coord;

	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(console, coord);
}

void ClearBuffer(void)
{
	SHORT row;
	SHORT col;

	for (row = 0; row < BUFFER_HEIGHT; ++row)
	{
		for (col = 0; col < BUFFER_WIDTH - 1; ++col)
			buffer[row][col] = ' ';

		buffer[row][BUFFER_WIDTH - 1] = '\0';
	}
}

void PrintBuffer(void)
{
	SHORT row;

	for (row = 0; row < CONSOLE_HEIGHT; ++row)
	{
		MoveCursor(0, row);
		printf(buffer[row]);
	}
}

void DrawSprite(short x, short y, char sprite)
{
	if (x < 0 || y < 0 || x >= CONSOLE_WIDTH || y >= CONSOLE_HEIGHT)
		return;

	buffer[y][x] = sprite;
}

void DrawString(short x, short y, const char* string)
{
	SHORT index;

	if (x < 0 || y < 0 || x >= CONSOLE_WIDTH || y >= CONSOLE_HEIGHT)
		return;

	for (index = 0; string[index] != '\0'; ++index)
	{
		if (x + index >= CONSOLE_WIDTH)
			break;

		buffer[y][x + index] = string[index];
	}
}

void ClearHUD(void)
{
	MoveCursor(0, CONSOLE_HEIGHT);
	printf(blankLine);
}
