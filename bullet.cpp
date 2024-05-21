#include "bullet.h"
#include "output.h"
#include "player.h"
#include "enemy.h"

#define BULLET_MAX		(200)
#define FRAMES_PER_MOVE	(2)

struct Bullet
{
	bool active;
	char moveCount;
	char type;
	char x;
	char y;
};

static Bullet bullet[BULLET_MAX];

void InitBullet(void)
{
	int index;

	for (index = 0; index < BULLET_MAX; ++index)
		bullet[index].active = false;
}

void AddBullet(char type, char x, char y)
{
	int index;

	for (index = 0; index < BULLET_MAX; ++index)
	{
		if (bullet[index].active)
			continue;

		bullet[index].active = true;
		bullet[index].moveCount = 0;
		bullet[index].type = type;
		bullet[index].x = x;
		bullet[index].y = y;

		return;
	}
}

void MoveBullet(void)
{
	int index;

	for (index = 0; index < BULLET_MAX; ++index)
	{
		if (bullet[index].active == false)
			continue;

		if (bullet[index].moveCount < FRAMES_PER_MOVE - 1)
		{
			bullet[index].moveCount += 1;
			continue;
		}

		bullet[index].moveCount = 0;

		if (bullet[index].type == 1)
			bullet[index].y -= 1;

		else if (bullet[index].type == 2)
			bullet[index].y += 1;

		if (bullet[index].y < 0 || bullet[index].y >= CONSOLE_HEIGHT)
			bullet[index].active = false;
	}
}

void DamageBullet(void)
{
	int index;

	for (index = 0; index < BULLET_MAX; ++index)
	{
		if (bullet[index].active == false)
			continue;

		if (bullet[index].type == 1)
		{
			if (IsEnemyHit(bullet[index].x, bullet[index].y))
				bullet[index].active = false;
		}
		else if (bullet[index].type == 2)
		{
			if (IsPlayerHit(bullet[index].x, bullet[index].y))
				bullet[index].active = false;
		}
	}
}

void DrawBullet(void)
{
	int index;

	for (index = 0; index < BULLET_MAX; ++index)
	{
		if (bullet[index].active == false)
			continue;

		if (bullet[index].type == 1)
			DrawSprite(bullet[index].x, bullet[index].y, 'o');
		else if (bullet[index].type == 2)
			DrawSprite(bullet[index].x, bullet[index].y, 'x');
	}
}
