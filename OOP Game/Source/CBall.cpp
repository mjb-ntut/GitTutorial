#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameMap.h"
#include "CBall.h"

namespace game_framework {
	/****************** CBall Class Declaration *****************/
	CBall::CBall()
	{
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
		vx = 5; vy = 0;
	}

	bool CBall::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		//tests whether a ball (rectangle bitmap) has hit another rectangle
		int x1 = x + dx;				
		int y1 = y + dy;				
		int x2 = x1 + bmp.Width();	
		int y2 = y1 + bmp.Height();	
		//overlap test					
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool CBall::IsAlive() const
	{
		return is_alive;
	}

	void CBall::LoadBitmap()
	{
		bmp.LoadBitmap(IDB_BALL, RGB(0, 0, 0));	//20x24 red cirlce bitmap
		bmp_center.LoadBitmap(IDB_CENTER, RGB(0, 0, 0)); //20x24 bitmap  
	}

	void CBall::OnMove()
	{
		if (!is_alive)
			return;
		x += vx;
		y += vy;
		delay_counter--;
		if (delay_counter < 0) {
			delay_counter = delay;

			const int STEPS = 18;
			static const int DIFFX[] = { 35, 32, 26, 17, 6, -6, -17, -26, -32, -34, -32, -26, -17, -6, 6, 17, 26, 32, };
			static const int DIFFY[] = { 0, 11, 22, 30, 34, 34, 30, 22, 11, 0, -11, -22, -30, -34, -34, -30, -22, -11, };
			index++;
			if (index >= STEPS)
				index = 0;
			dx = DIFFX[index];
			dy = DIFFY[index];
		}
	}

	void CBall::SetDelay(int d)
	{
		delay = d;
	}

	bool CBall::OffScreen(CGameMap *m)
	{
		//CHECK IF OBJECT IS ON SCREEN
		return (x < m->getSX() || y < m->getSY() || x > m->getSX() + 640 || y > m->getSY() + 480);
	}

	void CBall::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void CBall::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CBall::OnShow(CGameMap *map)
	{
		if (is_alive) {
			//bmp is set at various coordinates that encircle bmp_center
			bmp.SetTopLeft(map->getScreenX(x + dx), map->getScreenY(y + dy));
			bmp.ShowBitmap();
			//bmp_center is located at the center of rotation
			bmp_center.SetTopLeft(map->getScreenX(x), map->getScreenY(y));
			bmp_center.ShowBitmap();
		}
	}
}