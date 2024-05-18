#pragma once

#include <windows.h>

enum KEY
{
	ESC = VK_ESCAPE,
	ENTER = VK_RETURN,
	SPACE = VK_SPACE,
	LEFT = VK_LEFT,
	UP = VK_UP,
	RIGHT = VK_RIGHT,
	DOWN = VK_DOWN
};

bool GetKeyDown(KEY key);
bool GetKey(KEY key);
