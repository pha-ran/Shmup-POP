#include "player.h"

#define PLAYER_CONFIG_FILE	"config\\player.txt"
#define PLAYER_INFO_PATH	"config\\player\\%s"
#define PLAYER_INFO_MAX		10

struct PlayerInfo
{
	char sprite;
	char maxHp;
	char framesPerMove;
	char framesPerAttack;
};

struct Player
{
	char type;
	char hp;
	char x;
	char y;
};

PlayerInfo playerInfo[PLAYER_INFO_MAX];
int playerInfoCount;
Player player;

void InitPlayerInfo(void)
{
	int index;
	char tokenBuffer[TOKEN_MAX];
	char fileName[PLAYER_INFO_MAX][TOKEN_MAX];

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
		playerInfo[index].framesPerAttack = atoi(tokenBuffer);
	}
}

void InitPlayer(char sprite, char x, char y)
{
	int index;

	for (index = 0; index < playerInfoCount; ++index)
	{
		if (sprite != playerInfo[index].sprite)
			continue;

		player.type = index;
		player.hp = playerInfo[index].maxHp;
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
	static int frameCount;

	if (frameCount < playerInfo[player.type].framesPerMove - 1)
	{
		++frameCount;
		return;
	}

	frameCount = 0;

	if (GetKey(UP))
		player.y -= 1;

	if (GetKey(DOWN))
		player.y += 1;

	if (GetKey(LEFT))
		player.x -= 1;

	if (GetKey(RIGHT))
		player.x += 1;

	if (player.x < 0)
		player.x = 0;

	if (player.y < 0)
		player.y = 0;

	if (player.x >= CONSOLE_WIDTH)
		player.x = CONSOLE_WIDTH - 1;

	if (player.y >= CONSOLE_HEIGHT)
		player.y = CONSOLE_HEIGHT - 1;
}

void DrawPlayer(void)
{
	if (player.hp <= 0)
		return;
	
	DrawSprite(player.x, player.y, playerInfo[player.type].sprite);

	MoveCursor(5, 29);
	printf("HP : %d", player.hp);

	MoveCursor(93, 29);
	printf("%03d,%03d", player.x, player.y);

	MoveCursor(86, 29);
	printf("%02d", playerInfo[player.type].framesPerMove);
}
