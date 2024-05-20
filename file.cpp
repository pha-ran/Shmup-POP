#pragma warning (disable : 6386)
#include "file.h"

static char fileBuffer[FILE_MAX];
static char* context;

void GetFirstToken(const char* const fileName, char* tokenBuffer)
{
	FILE* file;
	long fileSize;

	fopen_s(&file, fileName, "rb");

	if (!file)
		__debugbreak();

	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);

	fseek(file, 0, SEEK_SET);
	fread(fileBuffer, 1, __min(fileSize, FILE_MAX), file);
	fclose(file);

	fileBuffer[__min(fileSize, FILE_MAX)] = '\0';

	context = NULL;
	strcpy_s(tokenBuffer, TOKEN_MAX, strtok_s(fileBuffer, DELIMITER, &context));
}

void GetNextToken(char* tokenBuffer)
{
	strcpy_s(tokenBuffer, TOKEN_MAX, strtok_s(NULL, DELIMITER, &context));
}
