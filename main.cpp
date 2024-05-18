#pragma comment (lib, "winmm.lib")

#include "input.h"
#include "output.h"
#include "player.h"

#define FRAMES_PER_SECOND		50
#define SECOND					1000
#define MILLISECONDS_PER_FRAME	SECOND / FRAMES_PER_SECOND

DWORD current;
DWORD previous;
DWORD previousSecond;
DWORD logicFrameCount;
DWORD renderFrameCount;

int main(void)
{
	timeBeginPeriod(1);

	InitConsole();
	InitPlayerInfo();
	InitPlayer('W', 59, 24);

	previous = timeGetTime();
	previousSecond = previous;

	for (;;)
	{
		MovePlayer();

		if (GetKey(ESC))
			Sleep(SECOND);

		current = timeGetTime();

		if (current - previousSecond >= SECOND)
		{
			MoveCursor(105, 29);
			printf("FPS %d(%d)  ", logicFrameCount, renderFrameCount);
			previousSecond += SECOND;
			logicFrameCount = 0;
			renderFrameCount = 0;
		}

		++logicFrameCount;

		if (current - previous >= MILLISECONDS_PER_FRAME)
		{
			previous += MILLISECONDS_PER_FRAME;
			continue;
		}
		else
		{
			Sleep(MILLISECONDS_PER_FRAME - (current - previous));
			previous += MILLISECONDS_PER_FRAME;
		}

		ClearBuffer();
		DrawPlayer();
		PrintBuffer();

		++renderFrameCount;
	}

	timeEndPeriod(1);

	return 0;
}
