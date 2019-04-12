#ifndef MONSTER_H
#define MONSTER_H

#include "CGameMap.h"

namespace game_framework {
	/****************** AABB Class Declaration *****************/
	class Monster
	{
	public:
		Monster();
		Monster(int, int);
		void OnMove(CGameMap*);
		void OnShow(CGameMap*);
		void AddBitmap(int, COLORREF);
		int getX() const;
		int getY() const;
		void SetTopLeft(int, int);
		void Reset();
		bool getAlive() const;
		void Hit();
		bool OnScreen(CGameMap*);
		CRect getMonsterRect();
		int monsterID;
		
	private:
		vector<CMovingBitmap> bmp;
		int index;
		int hit_count;
		//bool BroadPhase(CGameMap*, float&);
		//bool TightSweep(CGameMap*, float&);
		int x, y;
		bool isAlive;
	};
}
#endif
