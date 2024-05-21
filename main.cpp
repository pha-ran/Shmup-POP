#pragma comment (lib, "winmm.lib")

#include "input.h"
#include "output.h"
#include "scene.h"
#include "stage.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include <stdio.h>
#include <windows.h>

#define FRAMES_PER_SECOND		(50)
#define SECOND					(1000)
#define MILLISECONDS_PER_FRAME	((SECOND) / (FRAMES_PER_SECOND))

void InitTime(void);
void PrintFPS(void);
bool CheckRenderSkip(void);

static Scene scene;
static DWORD current;
static DWORD previous;
static DWORD previousSecond;
static DWORD logicFrameCount;
static DWORD renderFrameCount;

int main(void)
{
	timeBeginPeriod(1);

	InitConsole();
	InitStageInfo();
	InitPlayerInfo();
	InitEnemyInfo();

	for (;;)
	{
		switch (scene)
		{
		case TITLE:
			if (GetKeyDown(ENTER))
			{
				scene = LOAD;
				break;
			}
			if (GetKeyDown(ESC))
			{
				scene = EXIT;
				break;
			}
			ClearBuffer();
			PrintTitle();
			break;

		case LOAD:
			if (!LoadStage())
			{
				scene = TITLE;
				break;
			}
			InitTime();
			scene = GAME;
			break;

		case GAME:
			// Logic
			if (!IsPlayerAlive())
			{
				scene = OVER;
				break;
			}
			if (!IsEnemyAlive())
			{
				scene = CLEAR;
				break;
			}
			MovePlayer();
			MoveEnemy();
			MoveBullet();
			FirePlayer();
			FireEnemy();
			DamageBullet();
			if (GetKey(ESC))
				Sleep(SECOND);
			// ~Logic

			// Frame
			current = timeGetTime();
			PrintFPS();
			if (CheckRenderSkip())
				continue;
			// ~Frame

			// Render
			ClearBuffer();
			DrawStage();
			DrawPlayer();
			DrawEnemy();
			DrawBullet();
			PrintBuffer();
			// ~Render
			break;

		case CLEAR:
			if (GetKeyDown(ENTER))
			{
				scene = LOAD;
				break;
			}
			PrintClear();
			break;

		case OVER:
			InitStage();
			if (GetKeyDown(ENTER))
			{
				scene = TITLE;
				break;
			}
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
	logicFrameCount = 0;
	renderFrameCount = 0;
}

void PrintFPS(void)
{
	if (current - previousSecond >= SECOND)
	{
		MoveCursor(CONSOLE_WIDTH - 15, CONSOLE_HEIGHT);
		printf("FPS %d(%d)  ", logicFrameCount, renderFrameCount);
		previousSecond += SECOND;
		logicFrameCount = 0;
		renderFrameCount = 0;
	}
}

bool CheckRenderSkip(void)
{
	DWORD frameTime = current - previous;

	previous += MILLISECONDS_PER_FRAME;
	++logicFrameCount;

	if (frameTime >= MILLISECONDS_PER_FRAME * 2)
		return true;
	else if (frameTime < MILLISECONDS_PER_FRAME)
		Sleep(MILLISECONDS_PER_FRAME - frameTime);

	++renderFrameCount;
	return false;
}
