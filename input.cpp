#include "input.h"
#include <windows.h>

#define KEY_MAX (0xFF)

static const unsigned char VK[KEY_MAX]
{
	VK_ESCAPE,
	VK_RETURN,
	VK_SPACE,
	VK_LEFT,
	VK_UP,
	VK_RIGHT,
	VK_DOWN
};

bool GetKeyDown(KEY key)
{
	static bool flag[KEY_MAX];

	if (GetAsyncKeyState(VK[key]) & 0x8000)
	{
		if (flag[key])
			return false;

		flag[key] = true;
		return true;
	}
	else
		flag[key] = false;

	return false;
}

bool GetKey(KEY key)
{
	if (GetAsyncKeyState(VK[key]) & 0x8000)
		return true;

	return false;
}
