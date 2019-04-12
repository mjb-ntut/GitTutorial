#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "LRDirection.h"

namespace game_framework {

	LRDirection::LRDirection()  
	{
		flag = false;
		key = 0;
	}

	void LRDirection::SetFlag(char nkey)
	{
		if (!flag)
		{
			flag = true;
			key = nkey;
		}
	}

	void LRDirection::ResetFlag(char nkey)
	{
		if (key == nkey)
			flag = false;
	}

	bool LRDirection::getDirection() const
	{
		const char KEY_LEFT = 37;
		const char KEY_RIGHT = 39;
		if (key == KEY_LEFT)
			return 0;
		else
			return 1; 
	}
}
