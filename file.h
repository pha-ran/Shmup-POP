#pragma once

#include <stdio.h>
#include <string.h>

#define FILE_MAX	4096
#define TOKEN_MAX	128
#define DELIMITER	" \t\r\n"

void GetFirstToken(const char* const fileName, char* tokenBuffer);
void GetNextToken(char* tokenBuffer);
