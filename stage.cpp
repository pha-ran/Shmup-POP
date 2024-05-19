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

StageInfo stageInfo;

void InitStageInfo(void)
{
	int index;
	char tokenBuffer[TOKEN_MAX];

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
	if (stageInfo.current >= stageInfo.count)
	{
		InitStage();
		return false;
	}

	InitEnemy();
	InitPlayer('W', 59, 24);
	AddEnemy('A', 59, 10);
	AddEnemy('B', 59, 11);
	AddEnemy('C', 59, 10);
	AddEnemy('D', 59, 10);
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
