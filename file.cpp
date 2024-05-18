#include "file.h"

static char fileBuffer[FILE_MAX];
static char* context;

void GetFirstToken(const char* const fileName, char* tokenBuffer)
{
	FILE* file;
	long fileSize;

	fopen_s(&file, fileName, "rb");
	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);

	fseek(file, 0, SEEK_SET);
	fread(fileBuffer, 1, fileSize, file);
	fclose(file);

	fileBuffer[fileSize] = '\0';

	context = NULL;
	strcpy_s(tokenBuffer, TOKEN_MAX, strtok_s(fileBuffer, DELIMITER, &context));
}

void GetNextToken(char* tokenBuffer)
{
	strcpy_s(tokenBuffer, TOKEN_MAX, strtok_s(NULL, DELIMITER, &context));
}
