#pragma once

#include "output.h"

enum Scene
{
	TITLE,
	LOAD,
	GAME,
	CLEAR,
	OVER,
	EXIT
};

void PrintTitle(void);
void PrintClear(void);
void PrintOver(void);
