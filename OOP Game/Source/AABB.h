#ifndef AABB_H
#define AABB_H

#include "CGameMap.h"
#include "LRDirection.h"

namespace game_framework {
	/****************** AABB Class Declaration *****************/
	class AABB
	{
	public:
		AABB();
		void OnMove(CGameMap*);
		void OnShow(CGameMap*);
		void AddBitmap(int, COLORREF);
		int getX() const;
		int getY() const;
		float getVX() const;
		float getVY() const;
		void setVX(float);
		void setVY(float);
		void SetTopLeft(int, int);
		bool OnGround(CGameMap*);
		void Reset();
		LRDirection direction;
	private:
		list<CMovingBitmap> bmp;
		list<CMovingBitmap>::iterator bmp_iter;
		bool BroadPhase(CGameMap*, float&);
		bool TightSweep(CGameMap*, float&);
		void UpdateLocation(float);
		void UpdateVelocity(float);
		void CRUpdateVelocity(CGameMap*);
		void newCoordinates(pair<int, int>&, pair<float, float>&, float) const;
		int x, y;
		float fx, fy; 
		float fvx, fvy;
		float fax, fay;
	};
}
#endif
