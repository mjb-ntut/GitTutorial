#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Rectangle.h"
#include "AABB.h"

namespace game_framework {
	/****************** AABB Class Definition *****************/
	AABB::AABB() : fvx(0.f), fvy(0.f), fax(0.f), fay(1.f)
	{}

	void AABB::OnMove(CGameMap *map)
	{
		float t_elapsed = 0.f;
		float lt_elapsed = 0.f;

		bool noCollision = false;
		
		while (fabs(1.f - t_elapsed) > 0.001f)
		{
			//update last time elapsed
			lt_elapsed = t_elapsed;
			//check for collsion using broad phase method
			noCollision = BroadPhase(map, t_elapsed);
			if (!noCollision)
				//check for collision using tight sweep method
				TightSweep(map, t_elapsed);
			
			UpdateLocation(t_elapsed - lt_elapsed);
			UpdateVelocity(t_elapsed - lt_elapsed);
	
			CRUpdateVelocity(map);
	
		}
		TRACE("OnMove() Loc: (%d, %d)\n", x, y);
		//Move Map to Accomodate Hero @ New Coordinates
		map->setSY(0);
		map->setSX(x);
	}

	void AABB::OnShow(CGameMap *map)
	{
		bmp.SetTopLeft(map->getScreenX(x), map->getScreenY(y));
		bmp.ShowBitmap();
	}

	void AABB::LoadBitmap()
	{
		//Change To More General Case Where Any Bitmap Can Be Loaded
		bmp.LoadBitmap(IDB_HERO);
	}

	float AABB::getVX() const
	{
		return fvx;
	}

	float AABB::getVY() const
	{
		return fvy;
	}

	void AABB::setVX(float nvx)
	{
		fvx = nvx;
	}

	void AABB::setVY(float nvy)
	{
		fvy = nvy;
	}

	void AABB::SetTopLeft(int nx, int ny)
	{
		x = nx;
		y = ny;
		fx = x + 0.f;
		fy = y + 0.f;
	}

	bool AABB::BroadPhase(CGameMap *map, float& time_elapsed)
	{
		float time_r = 1.f - time_elapsed;

		CRect origRect(x, y, x + bmp.Width(), y + bmp.Height());
		origRect.NormalizeRect();
		
		pair<int, int> nnc;
		pair<float, float> nfc;
		newCoordinates(nnc, nfc, time_r);
		
		CRect destRect(CPoint(nnc.first, nnc.second), origRect.Size());
		destRect.NormalizeRect();
		
		CRect bphaseRect;
		bphaseRect.UnionRect(origRect, destRect);

		// check if broad phase area is within the map boundaries
		if (map->offMap(bphaseRect))
			return false; 

		// Check if braod phase area is free of obstacles
		if (map->isEmpty(bphaseRect))
		{
			time_elapsed = 1.f;
			return true;
		}	
		else
			// Obstacle present in broad phase area
			return false;
	}

	bool AABB::TightSweep(CGameMap *map, float& time_elapsed)
	{
		const float dt = 0.001f;
		
		CRect origRect(x, y, x + bmp.Width(), y + bmp.Height());
		origRect.NormalizeRect();

		CRect destRect(origRect);

		for (auto i = 0; fabs(1.001f - time_elapsed) > 0.001f; i++)
		{
			pair<int, int> nnc;
			pair<float, float> nfc;
			newCoordinates(nnc, nfc, i * dt);
			
			destRect.MoveToXY(CPoint(nnc.first, nnc.second));

			if ( map->offMap(destRect) || map->pCollision(destRect))
			{
				if(i > 0)
					time_elapsed -= dt;
				return false;
			}

			time_elapsed += dt;
		}
	
		time_elapsed = 1.f;
		return true;
	}

	void AABB::UpdateLocation(float time)
	{
		pair<int, int> nnc;
		pair<float, float> nfc;
		newCoordinates(nnc, nfc, time);

		x = nnc.first; y = nnc.second;
		fx = nfc.first; fy = nfc.second;
	}

	void AABB::UpdateVelocity(float time)
	{
		fvx += fax * time;
		fvy += fay * time;
	}

	void AABB::CRUpdateVelocity(CGameMap *map)
	{
		
		CRect testRect(CPoint(x, y), CSize(bmp.Width(), bmp.Height()));
		testRect.NormalizeRect();

		//Left Side Collision Test
		if (fvx < 0.f)
		{
			testRect.MoveToXY(x - 1, y);
			if (map->lCollision(testRect) || map->offMap(testRect))
			{
				fx = x + 0.f;
				fvx = 0.f;
			}
				
		}
		//Right Side Collision Test
		if(fvx > 0.f)
		{
			testRect.MoveToXY(x + 1, y);
			if (map->rCollision(testRect) || map->offMap(testRect))
			{
				fx = x + 0.f;
				fvx = 0.f;
			}
				
		}
		//Top Side Collision Test
		if (fvy < 0.f)
		{
			testRect.MoveToXY(x, y - 1);
			if (map->tCollision(testRect) || map->offMap(testRect))
			{
				fy = y + 0.f;
				fvy = 0.f;
			}
		}
		//Bottom Side Collision Test
		if (fvy > 0.f)
		{
			testRect.MoveToXY(x, y + 1);
			if (map->bCollision(testRect) || map->offMap(testRect))
			{
				fy = y + 0.f;
				fvy = 0.f;
			}
		}
			
	}

	void AABB::newCoordinates(pair<int, int>& nnc, pair<float, float>& nfc, float time) const
	{
		nfc.first = fx + fvx * time + 0.5f * fax * pow(time, 2.f);
		if (fvx < 0)
			nnc.first = static_cast<int>(ceilf(nfc.first));
		else
			nnc.first = static_cast<int>(floorf(nfc.first));

		nfc.second = fy + fvy * time + 0.5f * fay * pow(time, 2.f);
		if (fvy < 0)
			nnc.second = static_cast<int>(ceilf(nfc.second));
		else
			nnc.second = static_cast<int>(floorf(nfc.second));
	}
}