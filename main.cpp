#include "input.h"
#include "output.h"
#include "file.h"

int main(void)
{
	InitConsole();

	char tokenBuffer[TOKEN_MAX];
	GetFirstToken("config\\player.txt", tokenBuffer);
	GetNextToken(tokenBuffer);
	GetNextToken(tokenBuffer);

	for (;;)
	{
		ClearBuffer();
		DrawString(57, 10, "test");
		DrawSprite(119, 29, 'e');
		PrintBuffer();
	}

	return 0;
}
