#include "input.h"

#define MAX_KEY_COUNT 0xFF

bool GetKeyDown(KEY key)
{
	static bool flag[MAX_KEY_COUNT];

	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (flag[key] == false)
		{
			flag[key] = true;
			return true;
		}
	}
	else
	{
		flag[key] = false;
	}

	return false;
}

bool GetKey(KEY key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;

	return false;
}
