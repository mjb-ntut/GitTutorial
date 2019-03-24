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
	AABB::AABB() : vx(0), vy(0)
	{}

	void AABB::OnMove(CGameMap *map)
	{
		const int STEPS_PER_FRAME = 1000;
			
		int currStep = 0; // holds the total number of differential steps taken
		int lastStep = 0; // holds the number of steps taken before obstacle or end

		CPoint offset(0, 0);

		while (currStep < STEPS_PER_FRAME)
		{
			lastStep = BroadPhase(map, offset, currStep);
			if (lastStep == 0) // broadphase background collision occurred
				lastStep = TightSweep(map, offset, currStep);
			
			UpdateLV(map, offset, lastStep);
		
			currStep += lastStep;
		}
		//Move Hero to New Coordinates
		x += offset.x;
		y += offset.y;
		TRACE("Hero: (%d, %d)\tMap: (%d,%d)\n", x, y, map->getSX(), map->getSY());
		//Move Map to Accomodate Hero @ New Coordinates
		map->setSX(x);
		map->setSY(0);
	}

	void AABB::OnShow(CGameMap *map)
	{
		//Change Because The Code Is Pretty Junky
		bmp.SetTopLeft(map->getScreenX(x), map->getScreenY(y)); // Needs to be Set In Screen Coordinates
		bmp.ShowBitmap();
	}

	void AABB::LoadBitmap()
	{
		//Change To More General Case Where Any Bitmap Can Be Loaded
		bmp.LoadBitmap(IDB_HERO);
	}

	int AABB::getVX() const
	{
		return vx;
	}

	int AABB::getVY() const
	{
		return vy;
	}

	void AABB::setVX(int nvx)
	{
		vx = nvx;
	}

	void AABB::setVY(int nvy)
	{
		vy = nvy;
	}

	void AABB::SetTopLeft(int nx, int ny)
	{
		x = nx;
		y = ny;
	}

	int AABB::BroadPhase(CGameMap *map, CPoint offset, int step_no)
	{
		//No. of Differential Steps per Frame
		const int STEPS_PER_FRAME = 1000;

		bool empty = true;
		//Problem IS Here
		CRect origRect(x, y, x + bmp.Width(), y + bmp.Height());
		origRect.MoveToXY(origRect.TopLeft() + offset);
		origRect.NormalizeRect();

		int x_offset = (STEPS_PER_FRAME - step_no) * vx / STEPS_PER_FRAME;
		int y_offset = (STEPS_PER_FRAME - step_no) * vy / STEPS_PER_FRAME;
		
		CRect destRect(origRect);
		destRect.NormalizeRect();
		destRect.MoveToXY(origRect.TopLeft() + CPoint(x_offset, y_offset));
	
		//bphaseRect is the smallest bounding-box containing current
		//and destination bounding-boxes
		CRect bphaseRect;
			
		bphaseRect.UnionRect(origRect, destRect);
		
		//check bphase is entirely inbounds
		
		if (map->offMap(bphaseRect))
		{
			TRACE("Out of Bounds!\n");
			return 0;
		}
			

		empty = map->isEmpty(bphaseRect);
		
		if (empty)
			return STEPS_PER_FRAME - step_no;
		return 0;
	}

	int AABB::TightSweep(CGameMap *map, CPoint offset, int step_no)
	{
		//no. of differential steps per frame (static const for class?)
		const int STEPS_PER_FRAME = 1000;

		bool xEmpty = true;
		bool yEmpty = true;

		CRect origRect(x, y, x + bmp.Width(), y + bmp.Height());
		origRect.MoveToXY(origRect.TopLeft() + offset);
		CRect dtDestR(origRect);

		for (auto i = 1; i < STEPS_PER_FRAME - step_no; i++)
		{
			int x_COffset = (i - 1) * vx / STEPS_PER_FRAME;
			int x_NOffset = i * vx / STEPS_PER_FRAME;
			
			int y_COffset = (i - 1) * vy / STEPS_PER_FRAME;
			int y_NOffset = i * vy / STEPS_PER_FRAME;

			

			
			if (abs(y_NOffset) > abs(y_COffset)) 
			{	
				// Check for General TB-Collision
				dtDestR.MoveToXY(origRect.TopLeft() + CPoint(x_COffset, y_NOffset));
				if (vy < 0)
					yEmpty = map->isEmptyH(dtDestR.top, dtDestR.left, dtDestR.right);
				else
					yEmpty = map->isEmptyH(dtDestR.bottom, dtDestR.left, dtDestR.right);
			}
			
			if (abs(x_NOffset) > abs(x_COffset))
			{// Check for LR-Collision
				dtDestR.MoveToXY(origRect.TopLeft() + CPoint(x_NOffset, y_COffset));
				if (vx < 0)
					xEmpty = map->isEmptyV(dtDestR.left, dtDestR.top, dtDestR.bottom);
				else
					xEmpty = map->isEmptyV(dtDestR.right, dtDestR.top, dtDestR.bottom);
			}
			//Record the additional number of steps taken during tightsweep before
			//a collision occurred.
			if (!xEmpty || !yEmpty)
			{
				TRACE("COLLISION @ Step: %d\n", step_no + i);
				return i;
			}
		}
		return STEPS_PER_FRAME - step_no;
	}

	void AABB::UpdateLV(CGameMap* map, CPoint& offset, int last_step)
	{
		const int STEPS_PER_FRAME = 1000;
		
		CRect origRect(x, y, x + bmp.Width(), y + bmp.Height());
		CRect currRect(origRect);
		

		bool xEmpty = true;
		int dx = last_step * vx / STEPS_PER_FRAME;
		int ny = (last_step - 1) * vy / STEPS_PER_FRAME;

		currRect.MoveToXY(origRect.TopLeft() + offset + CPoint(dx, ny));
		if (vx < 0)
			xEmpty = map->isEmptyV(currRect.left, currRect.top, currRect.bottom);
		else
			xEmpty = map->isEmptyV(currRect.right, currRect.top, currRect.bottom);
				
		bool yEmpty = true;
		int nx = (last_step - 1) * vx / STEPS_PER_FRAME;
		int dy = last_step * vy / STEPS_PER_FRAME;
		currRect.MoveToXY(origRect.TopLeft() + offset + CPoint(nx, dy));
		if (vy < 0)
			yEmpty = map->isEmptyH(currRect.top, currRect.left, currRect.right);
		else
			yEmpty = map->isEmptyH(currRect.bottom, currRect.left, currRect.right);
		
		//update x- & y-direction location
		if (xEmpty && yEmpty)
			offset += CPoint(dx, dy);
		else
			offset += CPoint(nx, ny);

		//update x- & y-direction velocity
		if(xEmpty == false)
		{
			TRACE("LR COLLISION\n");
			vx = 0;
		}
		if (yEmpty == false)
		{
			TRACE("TB COLLISION\n");
			vy = 0;
		}
		if (!xEmpty || !yEmpty)
			TRACE("NEW VELOICTY: (%d, %d)\n", vx, vy);
	}
}