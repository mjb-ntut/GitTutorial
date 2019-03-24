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
		if (offMap(r))
			return false;

		for(auto i = r.left / BW; i <= r.right / BW; i++ )
			for (auto j = r.top / BH; j <= r.bottom / BH; j++)
			{
				if (map_blocks[j][i] != 0)
					return false;
			}
		return true;
	}
	
	bool CGameMap::isEmptyH(int y, int x_init, int x_fin) const
	{
		if (offMap(CPoint(x_init, y)) || offMap(CPoint(x_fin, y)))
			return false;
		for (auto i = x_init / BW; i <= x_fin / BW; i++)
			if (map_blocks[y / BH][i] != 0)
				return false;
		return true;
	}

	bool CGameMap::isEmptyV(int x, int y_init, int y_fin) const
	{
		if (offMap(CPoint(x, y_fin)) || offMap(CPoint(x, y_init)))
			return false;
		for (auto i = y_init / BH; i <= y_fin / BH; i++)
			if (map_blocks[i][x / BW] != 0)
				return false;
		return true;
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
		if (nx - 320 + 22 < MAP_MIN_X)
			sx = MAP_MIN_X;
		else if (nx + 320 + 22 > MAP_MAX_X)
			sx = MAP_MAX_X - 640;
		else
			sx = nx - 320 + 22;
	}

	void CGameMap::setSY(int ny)
	{
		//sy = ny;
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