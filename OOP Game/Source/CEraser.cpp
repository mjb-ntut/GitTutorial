#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"

namespace game_framework {
	/****************** CEraser Class Definition *****************/
	class CGameMap;
	CEraser::CEraser()
	{
		//Initialize() sets CAnimation to initial position.
		//Initialize() sets all isMoving boolean data members to false.
		Initialize();
	}

	int CEraser::GetX1()
	{
		return x;
	}

	int CEraser::GetY1()
	{
		return y;
	}

	int CEraser::GetX2()
	{
		return x + animation.Width();
	}

	int CEraser::GetY2()
	{
		return y + animation.Height();
	}

	void CEraser::Initialize()
	{
		const int X_POS = 280;
		const int Y_POS = 400;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CEraser::LoadBitmap()
	{
		animation.AddBitmap(IDB_ERASER1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER3, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
	}

	void CEraser::OnMove(CGameMap* m)
	{
		const int STEP_SIZE = 2;
		animation.OnMove();
		if (isMovingLeft)
		{
			velocity.first = -1 * STEP_SIZE;
		}
		else if (isMovingRight)
		{
			velocity.first = STEP_SIZE;
		}
		else
			velocity.first = 0;

		if (isMovingUp)
		{
			velocity.second = -1 * STEP_SIZE;
		}
		else if (isMovingDown)
		{
			velocity.second = STEP_SIZE;
		}
		else
			velocity.second = 0;

		int temp_x = x + velocity.first;
		int temp_y = y + velocity.second;

		if (m->isEmpty(temp_x, y))
		{
			x = temp_x;
			//Code Needs to Be Cleaned...Need Variable Name for Screen Width
			if (m->getScreenX(x) < 0.2 * 640 && velocity.first < 0)
				m->setSX(m->getSX() + velocity.first);
			if(m->getScreenX(x) > 0.8 * 640 && velocity.first > 0)
				m->setSX(m->getSX() + velocity.first);
		}

		if (m->isEmpty(x, temp_y))
		{
			y = temp_y;
			//Code Needs to Be Cleaned...Need Variable Name for Screen Width
			if (m->getScreenY(y) < 0.2 * 480 && velocity.second < 0)
				m->setSY(m->getSY() + velocity.second);
			if (m->getScreenY(y) > 0.8 * 480 && velocity.second > 0)
				m->setSY(m->getSY() + velocity.second);
		}
	}

	void CEraser::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CEraser::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CEraser::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CEraser::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CEraser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CEraser::OnShow(CGameMap *m)
	{
		animation.SetTopLeft(m->getScreenX(x), m->getScreenY(y));
		animation.OnShow();
	}

	bool CEraser::isTouchingGround(CGameMap *m)
	{
		const int GROUND_VALUE = 2;
		return (m->isObstacle(x, y + animation.Height()) == GROUND_VALUE);
	};

	void CEraser::Jump(CGameMap *m)
	{
		if(isTouchingGround(m))
		{ 
			velocity.first = 2;
			velocity.second = -20;
		}
	}
}