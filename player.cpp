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
	bool alive;
	char hp;
	char x;
	char y;
};

PlayerInfo playerInfo[PLAYER_INFO_MAX];
Player player;

void InitPlayerInfo()
{
	int index;
	int playerInfoCount;
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
