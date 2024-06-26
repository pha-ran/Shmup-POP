#include "player.h"
#include "input.h"
#include "output.h"
#include "file.h"
#include "bullet.h"
#include <stdio.h>
#include <stdlib.h>

#define PLAYER_CONFIG_FILE	"config\\player.txt"
#define PLAYER_INFO_PATH	"config\\player\\%s"
#define PLAYER_INFO_MAX		(10)

struct PlayerInfo
{
	char sprite;
	char maxHp;
	char framesPerMove;
	char framesPerFire;
};

struct Player
{
	char type;
	char hp;
	char moveCount;
	char fireCount;
	char x;
	char y;
};

static PlayerInfo playerInfo[PLAYER_INFO_MAX];
static int playerInfoCount;
static Player player;

void InitPlayerInfo(void)
{
	char tokenBuffer[TOKEN_MAX];
	char fileName[PLAYER_INFO_MAX][TOKEN_MAX];
	int index;

	GetFirstToken(PLAYER_CONFIG_FILE, tokenBuffer);
	playerInfoCount = atoi(tokenBuffer);

	for (index = 0; index < playerInfoCount; ++index)
	{
		GetNextToken(tokenBuffer);
		sprintf_s(fileName[index], PLAYER_INFO_PATH, tokenBuffer);
	}

	for (index = 0; index < playerInfoCount; ++index)
	{
		GetFirstToken(fileName[index], tokenBuffer);
		playerInfo[index].sprite = tokenBuffer[0];

		GetNextToken(tokenBuffer);
		playerInfo[index].maxHp = atoi(tokenBuffer);

		GetNextToken(tokenBuffer);
		playerInfo[index].framesPerMove = atoi(tokenBuffer);

		GetNextToken(tokenBuffer);
		playerInfo[index].framesPerFire = atoi(tokenBuffer);
	}
}

void InitPlayer(char sprite, char x, char y)
{
	int index;

	player.hp = 0;

	for (index = 0; index < playerInfoCount; ++index)
	{
		if (sprite != playerInfo[index].sprite)
			continue;

		player.type = index;
		player.hp = playerInfo[index].maxHp;
		player.moveCount = 0;
		player.fireCount = 0;
		player.x = x;
		player.y = y;

		break;
	}
}

bool IsPlayerAlive(void)
{
	return player.hp > 0;
}

void MovePlayer(void)
{
	if (player.moveCount < playerInfo[player.type].framesPerMove - 1)
	{
		player.moveCount += 1;
		return;
	}

	if (GetKey(UP))
	{
		player.y -= 1;
		player.moveCount = 0;
	}

	if (GetKey(DOWN))
	{
		player.y += 1;
		player.moveCount = 0;
	}

	if (GetKey(LEFT))
	{
		player.x -= 1;
		player.moveCount = 0;
	}

	if (GetKey(RIGHT))
	{
		player.x += 1;
		player.moveCount = 0;
	}

	if (player.x < 0)
		player.x = 0;

	if (player.y < 0)
		player.y = 0;

	if (player.x >= CONSOLE_WIDTH)
		player.x = CONSOLE_WIDTH - 1;

	if (player.y >= CONSOLE_HEIGHT)
		player.y = CONSOLE_HEIGHT - 1;
}

void FirePlayer(void)
{
	if (player.fireCount < playerInfo[player.type].framesPerFire - 1)
	{
		player.fireCount += 1;
		return;
	}

	if (GetKey(SPACE))
	{
		AddBullet(1, player.x, player.y - 1);
		player.fireCount = 0;
	}
}

bool IsPlayerHit(char x, char y)
{
	if (x == player.x && y == player.y)
	{
		player.hp -= 1;
		return true;
	}

	return false;
}

void DrawPlayer(void)
{
	if (player.hp <= 0)
		return;
	
	DrawSprite(player.x, player.y, playerInfo[player.type].sprite);

	MoveCursor(5, 29);
	printf("HP : %d", player.hp);
}
