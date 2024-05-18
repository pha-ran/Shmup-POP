#include "input.h"
#include "output.h"
#include "player.h"

int main(void)
{
	InitConsole();
	InitPlayerInfo();
	InitPlayer('W', 59, 24);

	for (;;)
	{
		MovePlayer();

		ClearBuffer();
		DrawPlayer();
		PrintBuffer();
	}

	return 0;
}
