#include "stage.h"

#define STAGE_CONFIG_FILE	"config\\stage.txt"
#define STAGE_INFO_PATH		"config\\stage\\%s"
#define STAGE_INFO_MAX		10

struct StageInfo
{
	char count;
	char current;
	char fileName[STAGE_INFO_MAX][TOKEN_MAX];
};

static StageInfo stageInfo;

void InitStageInfo(void)
{
	char tokenBuffer[TOKEN_MAX];
	int index;

	GetFirstToken(STAGE_CONFIG_FILE, tokenBuffer);
	stageInfo.count = atoi(tokenBuffer);

	for (index = 0; index < stageInfo.count; ++index)
	{
		GetNextToken(tokenBuffer);
		sprintf_s(stageInfo.fileName[index], STAGE_INFO_PATH, tokenBuffer);
	}
}

void InitStage(void)
{
	stageInfo.current = 0;
}

bool LoadStage(void)
{
	char tokenBuffer[TOKEN_MAX];
	int count;
	char sprite;
	char x;
	char y;

	if (stageInfo.current >= stageInfo.count)
	{
		InitStage();
		return false;
	}

	InitEnemy();
	InitPlayer(0, 0, 0);
	InitBullet();

	GetFirstToken(stageInfo.fileName[stageInfo.current], tokenBuffer);
	count = atoi(tokenBuffer);

	GetNextToken(tokenBuffer);
	sprite = tokenBuffer[0];

	GetNextToken(tokenBuffer);
	x = atoi(tokenBuffer);

	GetNextToken(tokenBuffer);
	y = atoi(tokenBuffer);

	InitPlayer(sprite, x, y);
	--count;

	while (count > 0)
	{
		GetNextToken(tokenBuffer);
		sprite = tokenBuffer[0];

		GetNextToken(tokenBuffer);
		x = atoi(tokenBuffer);

		GetNextToken(tokenBuffer);
		y = atoi(tokenBuffer);

		AddEnemy(sprite, x, y);

		--count;
	}
	
	stageInfo.current += 1;

	return true;
}

void DrawStage(void)
{
	if (stageInfo.current >= stageInfo.count)
	{
		MoveCursor(55, 29);
		printf("LAST STAGE");
		return;
	}

	MoveCursor(57, 29);
	printf("STAGE %d", stageInfo.current);
}
