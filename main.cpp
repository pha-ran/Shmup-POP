#include "input.h"
#include "output.h"
#include "player.h"

int main(void)
{
	InitConsole();
	InitPlayerInfo();

	for (;;)
	{
		ClearBuffer();
		DrawString(57, 10, "test");
		DrawSprite(119, 29, 'e');
		PrintBuffer();
	}

	return 0;
}
