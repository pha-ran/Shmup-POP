#include "scene.h"

void PrintTitle(void)
{
	ClearBuffer();
	DrawString(47, 7, "C o n s o l e   S h m u p");
	DrawString(50, 19, "press enter to start");
	DrawString(51, 21, "press esc to exit");
	PrintBuffer();
}

void PrintClear(void)
{
	DrawString(55, 14, "C L E A R");
	DrawString(54, 16, "press enter");
	PrintBuffer();
}

void PrintOver(void)
{
	DrawString(52, 14, "G A M E O V E R");
	DrawString(54, 16, "press enter");
	PrintBuffer();
}
