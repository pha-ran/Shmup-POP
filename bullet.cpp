#include "bullet.h"

#define BULLET_MAX		200
#define FRAMES_PER_MOVE	3

struct Bullet
{
	bool active;
	char type;
	char x;
	char y;
};

Bullet bullet[BULLET_MAX];

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
		bullet[index].type = type;
		bullet[index].x = x;
		bullet[index].y = y;

		return;
	}
}

void MoveBullet(void)
{
	static int frameCount[BULLET_MAX];
	int index;

	for (index = 0; index < BULLET_MAX; ++index)
	{
		if (bullet[index].active == false)
			continue;

		if (frameCount[index] < FRAMES_PER_MOVE - 1)
		{
			frameCount[index] += 1;
			continue;
		}

		frameCount[index] = 0;

		if (bullet[index].type == 1)
			bullet[index].y -= 1;

		else if (bullet[index].type == 2)
			bullet[index].y += 1;

		if (bullet[index].y < 0 || bullet[index].y >= CONSOLE_HEIGHT)
			bullet[index].active = false;
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
