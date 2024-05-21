#pragma once

enum KEY
{
	ESC,
	ENTER,
	SPACE,
	LEFT,
	UP,
	RIGHT,
	DOWN
};

bool GetKeyDown(KEY key);
bool GetKey(KEY key);
