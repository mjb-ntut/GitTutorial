#ifndef AABB_H
#define AABB_H

#include "CGameMap.h"

namespace game_framework {
	/****************** AABB Class Declaration *****************/
	class AABB
	{
	public:
		AABB();
		void OnMove(CGameMap*);
		void OnShow(CGameMap*);
		void LoadBitmap();
		int getVX() const;
		int getVY() const;
		void setVX(int);
		void setVY(int);
		void SetTopLeft(int, int);
	private:
		CMovingBitmap bmp;
		int BroadPhase(CGameMap*, CPoint, int);
		int TightSweep(CGameMap*, CPoint, int);
		void UpdateLV(CGameMap*, CPoint& , int);
		int x, y; // Absolute Location
		int vx, vy;
	};
}
#endif
