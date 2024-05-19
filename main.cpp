#pragma comment (lib, "winmm.lib")

#include "input.h"
#include "output.h"
#include "scene.h"
#include "player.h"
#include "enemy.h"

#define FRAMES_PER_SECOND		50
#define SECOND					1000
#define MILLISECONDS_PER_FRAME	SECOND / FRAMES_PER_SECOND

Scene scene;
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
	InitEnemyInfo();

	for (;;)
	{
		switch (scene)
		{
		case TITLE:
			if (GetKeyDown(ENTER))
				scene = LOAD;
			if (GetKeyDown(ESC))
				scene = EXIT;
			PrintTitle();
			break;

		case LOAD:
			InitPlayer('W', 59, 24);
			InitTime();
			scene = GAME;
			break;

		case GAME:
			// Logic
			MovePlayer();
			if (GetKey(ESC))
				Sleep(SECOND);
			// ~Logic

			// Frame
			current = timeGetTime();
			PrintFPS();
			++logicFrameCount;
			if (CheckRenderSkip())
				continue;
			// ~Frame

			// Render
			ClearBuffer();
			DrawPlayer();
			PrintBuffer();
			++renderFrameCount;
			// ~Render
			break;

		case CLEAR:
			if (GetKeyDown(ENTER))
				scene = LOAD;
			PrintClear();
			break;

		case OVER:
			if (GetKeyDown(ENTER))
				scene = TITLE;
			PrintOver();
			break;

		default:
			timeEndPeriod(1);
			return 0;
		}
	}
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
