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

void InitTime(void);
void PrintFPS(void);
bool CheckRenderSkip(void);

int main(void)
{
	timeBeginPeriod(1);

	InitConsole();
	InitPlayerInfo();
	InitPlayer('W', 59, 24);
	InitTime();

	for (;;)
	{
		// Logic
		MovePlayer();

		if (GetKey(ESC))
			Sleep(SECOND);
		// ~Logic

		// Check Render Skip
		current = timeGetTime();
		PrintFPS();
		++logicFrameCount;
		if (CheckRenderSkip())
			continue;
		// ~Check Render Skip

		// Render
		ClearBuffer();
		DrawPlayer();
		PrintBuffer();
		++renderFrameCount;
		// ~Render
	}

	timeEndPeriod(1);

	return 0;
}

void InitTime(void)
{
	previous = timeGetTime();
	previousSecond = previous;
}

void PrintFPS(void)
{
	if (current - previousSecond >= SECOND)
	{
		MoveCursor(105, 29);
		printf("FPS %d(%d)  ", logicFrameCount, renderFrameCount);
		previousSecond += SECOND;
		logicFrameCount = 0;
		renderFrameCount = 0;
	}
}

bool CheckRenderSkip(void)
{
	if (current - previous >= MILLISECONDS_PER_FRAME)
	{
		previous += MILLISECONDS_PER_FRAME;
		return true;
	}

	Sleep(MILLISECONDS_PER_FRAME - (current - previous));
	previous += MILLISECONDS_PER_FRAME;

	return false;
}
