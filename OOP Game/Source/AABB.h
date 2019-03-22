#ifndef AABB_H
#define AABB_H

#include "CGameMap.h"

namespace game_framework {
	/****************** AABB Class Declaration *****************/
	class AABB
	{
	public:
		AABB();
		void OnMove(CGameMap *m);
		void OnShow();
		void LoadBitmap();
		int getVX() const;
		int getVY() const;
		void setVX(int);
		void setVY(int);
		bool BBroadSweep(CGameMap *m) const;
		float BTightSweep(CGameMap *m) const;
		float BTightSweep2(CGameMap *m) const;
	//private:
		CMovingBitmap bmp;
		int vx, vy;
	};
}
#endif
