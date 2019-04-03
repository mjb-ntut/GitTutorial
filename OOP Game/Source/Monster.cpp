#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Monster.h"

namespace game_framework {
	/****************** Monster Class Definition *****************/
	Monster::Monster()
	{
		hit_count = 3;
		isAlive = true;
		index = 0;
	}

	Monster::Monster(int nx, int ny) : x(nx), y(ny)
	{
		hit_count = 3;
		isAlive = true;
		index = 0;
	}
	
	void Monster::OnMove(CGameMap* map)
	{}

	void Monster::OnShow(CGameMap* map)
	{
		bmp[index].SetTopLeft(map->getScreenX(x), map->getScreenY(y));
		bmp[index].ShowBitmap();
	}
	
	int Monster::getX() const
	{
		return x;
	}

	int Monster::getY() const
	{
		return y;
	}
	
	void Monster::SetTopLeft(int nx, int ny)
	{
		x = nx;
		y = ny;
	}
	
	void Monster::AddBitmap(int IDB_BITMAP, COLORREF colorkey)
	{
		//Change To More General Case Where Any Bitmap Can Be Loaded
		CMovingBitmap add_bmp;
		add_bmp.LoadBitmap(IDB_BITMAP, colorkey);
		bmp.push_back(add_bmp);
		Reset();
	}

	void Monster::Reset()
	{
		GAME_ASSERT(bmp.size() != 0, "CAnimation: Bitmaps must be loaded first.");
		index = 0;
	}

	bool Monster::getAlive() const
	{
		return isAlive;
	}

	void Monster::Hit()
	{
		if (hit_count > 0)
			hit_count--;
		else
		{
			isAlive = false;
			index = 1;
		}
	}

	bool Monster::OnScreen(CGameMap* map)
	{
		//CODE NEEDS TO BE CLEANED UP A LOT
		//1. NEED TO CONSIDER CHANGING MONSTER SIZES
		//2. NEED TO CLEAN UP CGAMEMAP SO IT HAS CONSTANT WIDTH & HEIGHT
		//3. NEED TO RESPECT THE BMP LOCATION ENCAPSULATION (SHOULD BE PRIVATE)

		CRect mRect(x, y, x + bmp[index].Width(), y + bmp[index].Height());
		
		mRect.NormalizeRect();
		
		return(mRect.left <= map->getSX() + 640 && mRect.right >= map->getSX(),
			mRect.top <= map->getSY() + 480 && mRect.bottom >= map->getSY());
	}

	CRect Monster::getMonsterRect()
	{
		//NEED TO RESPECT ENCAPSULATION FOR CMOVINGBITMAP (LOCATION IS PRIVATE)
		CRect mRect(x, y, x + bmp[index].Width(), y + bmp[index].Height());
		
		return(mRect);
	}


}