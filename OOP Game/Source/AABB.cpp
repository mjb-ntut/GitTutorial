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

	void AABB::OnMove(CGameMap *m)
	{
		if (vx != 0 || vy != 0)
		{
			if (BBroadSweep(m)) //BBroadSweep Returns True No Collisions
				bmp.SetTopLeft(bmp.Left() + vx, bmp.Top() + vy);
			else
			{ 
				//Else Run The Super Slow Collision Algorithm
				float f = BTightSweep(m);
				float f2 = BTightSweep2(m);
				int fvx = static_cast<int>(f * vx);
				int fvy = static_cast<int>(f * vy);
				bmp.SetTopLeft(bmp.Left() + fvx, bmp.Top() + fvy);
			}
		}
		//vx = vy = 0;
	}

	void AABB::OnShow()
	{
		//Change Because The Code Is Pretty Junky
		bmp.SetTopLeft(bmp.Left(), bmp.Top());
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

	bool AABB::BBroadSweep(CGameMap *m) const
	{
		//Create Broadsweep Rectangle: A Minimum Bounding Rectangle of both the 
		//Original AABB (AABB @ t) and Updated AABB (AABB @ t + dt)
		//We are going to take advantage of the fact that CMovingBitmap has a CRect
		//CRect::UnionRect Creates a Minimum Bounding Rectangle that Contains both Rectangles
		CRect bmpDest, bsweep;
		TRACE("Original Rect: (%d, %d)\t(%d, %d)\n", bmp.location.left, bmp.location.top, bmp.location.right, bmp.location.bottom);
		bmpDest.CopyRect(bmp.location);
		bmpDest.MoveToXY(bmp.location.TopLeft() + CPoint(vx, vy));
		TRACE("Dest. Rect: (%d, %d)\t(%d, %d)\n", bmpDest.left, bmpDest.top, bmpDest.right, bmpDest.bottom);
		bsweep.UnionRect(bmp.location, bmpDest);
		TRACE("Broadsweep Rect: (%d, %d)\t(%d, %d)\n", bsweep.left, bsweep.top, bsweep.right, bsweep.bottom);
		//Check Broadsweep Box Intersects w/ Any CGameMap Obstacles 
		for(auto i = bsweep.left / m->BW; i <= bsweep.right / m->BW; i++)
			for(auto j = bsweep.top / m->BH; j <= bsweep.bottom / m->BH ; j++)
			{ 
				if (m->map_blocks[j][i] != 0)
				{
					TRACE("Potential Intersection: Block(%d, %d)\n", j, i);
					return false;
				}
			}
		return true;
	}

	float AABB::BTightSweep(CGameMap *m) const
	{
		//Need To Create A Temporary Rectanlge With Which to Compare W/ Map Blocks
		CRect temp;
		temp.CopyRect(bmp.location);
		//Need To Create A Step Count (STEPS_PER_FRAME)
		const int STEPS_PER_FRAME = 1000;
		//Need To Move Our BitMap to Last Known Good Position
		//Position Will Be Fractions of a Pixel
		double fx, fy;
		//Probably Should Revamp With a While-Loop or Do-While-Loop
		for (auto k = 0; k < STEPS_PER_FRAME; k++)
		{
			fx = k * static_cast<double>(vx) / STEPS_PER_FRAME;
			fy = k * static_cast<double>(vy) / STEPS_PER_FRAME;
			
			int new_x = bmp.location.left + static_cast<int>(round(fx));
			int new_y = bmp.location.top + static_cast<int>(round(fy));

			temp.MoveToXY(new_x, new_y);

			for (auto i = temp.left / m->BW; i <= temp.right / m->BW; i++)
				for (auto j = temp.top / m->BH; j <= temp.bottom / m->BH; j++)
				{
					if (m->map_blocks[j][i] != 0)
					{
						TRACE("Potential Intersection: Block(%d, %d)\n", j, i);
						TRACE("Fractional Distance: %f\n", static_cast<float>(k) / STEPS_PER_FRAME);
						return static_cast<float>(k-1) / STEPS_PER_FRAME;
					}
				}
		}
		TRACE("Fractional Distance: 1.0 (No Collision)\n");
		return 1.f;
	}

	float AABB::BTightSweep2(CGameMap *m) const
	{
		//These Comments And This Code Needs To Be Cleaned Up At Some Point
		//This Function Aims To Improve The Speed OF BTightSweep Though There Are
		//Several Considerations.
		//1. Similar to BTightSweep This Function Only Aims to Check Collision w/ Background
		//2. An Important Assumption That The Incremental Time dt Is Small Enough Thar
		//   No Edge Could Possibly Miss A Map Block (BG Obstacle) Entirely This
		//   This Depends of Veloicty, BlockSize & Time Step
		//3. That Only A Leading Edge Will Be First To Hit An Obstacle (May Discard
		//   Since Not So Sure About this Assumption It Seems Correct But May Be Wrong
		//Make Point2f Class Like OpenCV that Class IT IS SWEET
		
		//Need To Create A Temporary Rectanlge With Which to Compare W/ Map Blocks
		CRect temp;
		temp.CopyRect(bmp.location);
		//Need To Create A Step Count (STEPS_PER_FRAME)
		const int STEPS_PER_FRAME = 1000;
		//Need To Move Our BitMap to Last Known Good Position
		//Position Will Be Fractions of a Pixel
		float fx, fy;
		
		for (auto k = 0; k < STEPS_PER_FRAME; k++)
		{
			fx = k * static_cast<float>(vx) / STEPS_PER_FRAME;
			fy = k * static_cast<float>(vy) / STEPS_PER_FRAME;
			//Throws fx, fy to Floor
			int new_x = bmp.location.left + static_cast<int>(fx);
			int new_y = bmp.location.top + static_cast<int>(fy);
			
			//Need To Test Leading Edge
			//Right & Left Edge
			bool isCollision = false;
			temp.MoveToXY(new_x, temp.top);
			for (auto i = temp.top / m->BH; i <= temp.bottom / m->BH; i++)
			{
				int n = 0;
				if (vx < 0)
				{ 
					n = m->isObstacle(temp.left, i * m->BH);
					if (n != 0)
					{
						TRACE("LEFT SIDE COLLISION\n");
						TRACE("OFFENDING BLOCK: [%d][%d]\n", i, temp.left/m->BW);
						isCollision = true;
					}
				}	
				else
				{ 
					n = m->isObstacle(temp.right, i * m->BH);
					if (n != 0)
					{
						TRACE("RIGHT SIDE COLLISION\n");
						TRACE("OFFENDING BLOCK: [%d][%d]\n", i, temp.right / m->BW);
						isCollision = true;
					}
				}	
			}

			//Top & Bottom Edge
			temp.MoveToXY(temp.left, new_y);
			for (auto i = temp.left / m->BW; i < temp.right / m->BW; i ++)
			{
				int n = 0;
				if (vy < 0)
				{
					n = m->isObstacle(i * m->BW, temp.top);
					if (n != 0)
					{
						TRACE("TOP SIDE COLLISION\n");
						TRACE("OFFENDING BLOCK: [%d][%d]\n", temp.top / m->BH, i);
						isCollision = true;
					}
				}
				else
				{
					n = m->isObstacle(i * m->BW, temp.bottom);
					if (n != 0)
					{
						TRACE("BOTTOM SIDE COLLISION\n");
						TRACE("OFFENDING BLOCK: [%d][%d]\n", temp.bottom / m->BH, i);
						isCollision = true;
					}
				}
			}
			if (isCollision)
			{
				float f3 = static_cast<float>(k) / STEPS_PER_FRAME;
				TRACE("COLLISION TIME: %f\n", f3);
				return f3;
			}
		}
		return 1.f;
	}
}