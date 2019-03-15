#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameMap.h"

namespace game_framework {
	
	CGameMap::CGameMap() : BW(128), BH(128), MAP_MIN_X(0), MAP_MAX_X(1024)
	{
		int temp[8][8] = {
		{ 1,0,0,0,0,0,1,1},
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 } };

		for(auto i = 0; i < 8; i++)
			for (auto j = 0; j < 8; j++)
			{
				map_blocks[i][j] = temp[i][j];
			}
		
	}

	void CGameMap::LoadBitmap()
	{
		map.LoadBitmap(IDB_TEST_MAP, RGB(255, 255, 255));
	}
	
	void CGameMap::OnShow()
	{
		map.SetTopLeft(-sx, -sy);
		map.ShowBitmap();
	} // end of CGameMap::OnShow()

	bool CGameMap::isEmpty(int x, int y) const
	{
		int gx = x / 128;
		int gy = y / 128;
		TRACE("(%d,%d) has value of %d.\n", x, y, map_blocks[gx][gy]);
		return (map_blocks[gy][gx] == 0);
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
		if (nx > MAP_MAX_X - 640)
			sx = MAP_MAX_X - 640;
		else if (nx < MAP_MIN_X)
			sx = MAP_MIN_X;
		else
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
}