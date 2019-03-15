#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBouncingBall.h"

namespace game_framework {

	/****************** CBouncingBall Class Definition *****************/
	CBouncingBall::CBouncingBall() : FLOOR(320)
	{
		location = pair<int, int>(280, 320); // 
		velocity = pair<int, int>(0, 0); //
		acceleration = pair<int, int>(0, 1);	//
		jerk = pair<int, int>(0, 0);
	}

	void CBouncingBall::LoadBitmap()
	{
		char *filename[4] = { ".\\bitmaps\\ball1.bmp",".\\bitmaps\\ball2.bmp",".\\bitmaps\\ball3.bmp",".\\bitmaps\\ball4.bmp" };
		for (int i = 0; i < 4; i++)
			animation.AddBitmap(filename[i], RGB(0, 0, 0));
	}

	void CBouncingBall::OnMove()
	{
		//
		if(location.second + velocity.second >= FLOOR)
		{ 
			location.second = FLOOR; /*Floor*/
			velocity.first = 0;
			velocity.second = 0;
		}
		else
		{
			location.first += velocity.first;
			location.second += velocity.second;
			velocity.second += acceleration.second;
		}
		animation.OnMove();	
	}

	void CBouncingBall::OnShow()
	{
		animation.SetTopLeft(location.first, location.second);
		animation.OnShow();
	}

	void CBouncingBall::Jump()
	{
		velocity.first = 2;
		velocity.second = -20;
	}
}