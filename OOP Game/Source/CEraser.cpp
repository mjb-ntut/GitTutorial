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
			if(m->isEmpty(x - STEP_SIZE, y))
			{
				x -= STEP_SIZE;
				if (m->getScreenX(x) < 300)
					m->setSX(m->getSX() - STEP_SIZE);
			}	
		}
		if (isMovingRight)
		{
			if(m->isEmpty(x+STEP_SIZE+80, y))
			{ 
				x += STEP_SIZE;
				if (m->getScreenX(x) > 300)
					m->setSX(m->getSX() + STEP_SIZE);
			}
		}
		if (isMovingUp)
		{
			y -= STEP_SIZE;
		}
		if (isMovingDown)
		{
			y += STEP_SIZE;
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
		//TRACE("E:(%d,%d)\tM:(%d,%d)\n", x, y, m->getSX(), m->getSY());
		animation.OnShow();
	}
}