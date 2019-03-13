#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameMap.h"

namespace game_framework {
	
	CGameMap::CGameMap() : BW(128), BH(128)
	{}

	void CGameMap::LoadBitmap()
	{
		map.LoadBitmap(IDB_TEST_MAP, RGB(255, 255, 255));
	}

	int CGameMap::getScreenX(int x) const
	{
		return x - sx;
	}

	int CGameMap::getScreenY(int y) const
	{
		return y - sy;
	}

	void CGameMap::setSX(int nx)
	{
		sx = nx;
	}

	void CGameMap::setSY(int ny)
	{
		sy = ny;
	}

	int CGameMap::getSX() const
	{
		return sx;
	}
	
	int CGameMap::getSY() const
	{
		return sy;
	}

	void CGameMap::OnShow()
	{
		map.SetTopLeft(sx, sy);
		map.ShowBitmap();
	} // end of CGameMap::OnShow()
}