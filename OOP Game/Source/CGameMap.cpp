#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameMap.h"

namespace game_framework {
	
	CGameMap::CGameMap() : BW(32), BH(32)
	{
		int temp[15][58] = {
			//Top Rows
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			//Forth Step
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1 },
			//Third Step
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			//Second Step
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			//First Step
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			//Bottom Rows
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
		};

		for(auto i = 0; i < 15; i++)
			for (auto j = 0; j < 58; j++)
			{
				map_blocks[i][j] = temp[i][j];
			}
		
	}

	void CGameMap::LoadBitmap()
	{
		map.LoadBitmap(IDB_MAP1A);
	}
	
	void CGameMap::OnShow()
	{
		map.SetTopLeft(-sx, -sy);
		map.ShowBitmap();
	} // end of CGameMap::OnShow()

	bool CGameMap::isEmpty(int x, int y) const
	{
		int gx = x / BW;
		int gy = y / BH;
		if (offMap(CPoint(x, y)))
			return false;
		return (map_blocks[gy][gx] == 0);
	}

	bool CGameMap::isEmpty(CRect r) const
	{
		for(auto i = r.left / BW; i <= r.right / BW; i++ )
			for (auto j = r.top / BH; j <= r.bottom / BH; j++)
			{
				if (map_blocks[j][i] != 0)
					return false;
			}
		return true;
	}
	
	bool CGameMap::pCollision(CRect r) const
	{
		return (bCollision(r) || rCollision(r) || tCollision(r) || lCollision(r));
	}

	bool CGameMap::bCollision(CRect r) const
	{
		//Test Bottom Border
		for (auto i = r.left / BW; i <= r.right / BW; i++)
			if (map_blocks[r.bottom / BH][i] != 0)
				return true;
		//No Collision Detected
		return false;
	}

	bool CGameMap::tCollision(CRect r) const
	{
		//Test Top Border
		for (auto i = r.left / BW; i <= r.right / BW; i++)
			if (map_blocks[r.top / BH][i] != 0)
				return true;
		return false;
	}
	
	bool CGameMap::lCollision(CRect r) const
	{
		//Test Left Border
		for (auto i = r.top / BH; i <= r.bottom / BH; i++)
			if (map_blocks[i][r.left / BW] != 0)
				return true;
		return false;
	}

	bool CGameMap::rCollision(CRect r) const
	{
		//Test Right Border
		for (auto i = r.top / BH; i <= r.bottom / BH; i++)
			if (map_blocks[i][r.right / BW] != 0)
				return true;
		return false;
	}

	bool CGameMap::offMap(CRect r) const
	{
		return(r.left < MAP_MIN_X || r.right > MAP_MAX_X
			|| r.top < MAP_MIN_Y || r.bottom > MAP_MAX_Y);
	}

	bool CGameMap::offMap(CPoint p) const
	{
		return(p.x < MAP_MIN_X || p.x > MAP_MAX_X
			|| p.y < MAP_MIN_Y || p.y > MAP_MAX_Y);
	}

	int CGameMap::getScreenX(int nx) const
	{
		//int nx = static_cast<float>(fnx);
		return nx - sx;
	}

	int CGameMap::getScreenY(int ny) const
	{
		//int ny = static_cast<float>(fny);
		return ny - sy;
	}

	void CGameMap::setSX(int nx)
	{
		//int nx = static_cast<int>(fnx);
		if (nx - 320 + 22 < MAP_MIN_X)
			sx = MAP_MIN_X;
		else if (nx + 320 + 22 > MAP_MAX_X)
			sx = MAP_MAX_X - 640;
		else
			sx = nx - 320 + 22;
	}

	void CGameMap::setSY(int ny)
	{
		sy = MAP_MIN_Y;
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