#include "input.h"
#include "output.h"

int main(void)
{
	InitConsole();

	for (;;)
	{
		ClearBuffer();
		DrawString(57, 10, "test");
		DrawSprite(119, 29, 'e');
		PrintBuffer();
	}

	return 0;
}
