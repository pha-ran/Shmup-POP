#include "enemy.h"

#define ENEMY_CONFIG_FILE		"config\\enemy.txt"
#define ENEMY_INFO_PATH			"config\\enemy\\%s"
#define ENEMY_INFO_MAX			10
#define ENEMY_MOVE_PATH			"config\\enemy\\move\\%s"
#define ENEMY_MOVE_COUNT_MAX	20
#define ENEMY_MAX				20

struct EnemyInfo
{
	char sprite;
	char maxHp;
	char framesPerMove;
	char framesPerAttack;
	char moveCount;
	char x[ENEMY_MOVE_COUNT_MAX];
	char y[ENEMY_MOVE_COUNT_MAX];
};

struct Enemy
{
	char type;
	char hp;
	char moveIndex;
	char x;
	char y;
};

EnemyInfo enemyInfo[ENEMY_INFO_MAX];
int enemyInfoCount;
Enemy enemy[ENEMY_MAX];
int enemyCount;

void InitEnemyInfo(void)
{
	int index;
	char tokenBuffer[TOKEN_MAX];
	char fileName[ENEMY_INFO_MAX][TOKEN_MAX];
	int moveIndex;
	char moveFileName[TOKEN_MAX];

	GetFirstToken(ENEMY_CONFIG_FILE, tokenBuffer);
	enemyInfoCount = atoi(tokenBuffer);

	for (index = 0; index < enemyInfoCount; ++index)
	{
		GetNextToken(tokenBuffer);
		sprintf_s(fileName[index], ENEMY_INFO_PATH, tokenBuffer);
	}

	for (index = 0; index < enemyInfoCount; ++index)
	{
		GetFirstToken(fileName[index], tokenBuffer);
		enemyInfo[index].sprite = tokenBuffer[0];

		GetNextToken(tokenBuffer);
		enemyInfo[index].maxHp = atoi(tokenBuffer);

		GetNextToken(tokenBuffer);
		enemyInfo[index].framesPerMove = atoi(tokenBuffer);

		GetNextToken(tokenBuffer);
		enemyInfo[index].framesPerAttack = atoi(tokenBuffer);

		GetNextToken(tokenBuffer);
		sprintf_s(moveFileName, ENEMY_MOVE_PATH, tokenBuffer);

		GetFirstToken(moveFileName, tokenBuffer);
		enemyInfo[index].moveCount = atoi(tokenBuffer);

		for (moveIndex = 0; moveIndex < enemyInfo[index].moveCount; ++moveIndex)
		{
			GetNextToken(tokenBuffer);
			enemyInfo[index].x[moveIndex] = atoi(tokenBuffer);

			GetNextToken(tokenBuffer);
			enemyInfo[index].y[moveIndex] = atoi(tokenBuffer);
		}
	}
}
