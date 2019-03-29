#ifndef CGAMEMAP_H
#define CGAMEMAP_H

namespace game_framework {
	
	class CGameMap
	{
	public:
		CGameMap();
		void LoadBitmap();
		void OnShow();
		bool isEmpty(int, int) const;
		bool isEmpty(CRect) const;
		bool pCollision(CRect) const;
		bool lCollision(CRect) const;
		bool rCollision(CRect) const;
		bool bCollision(CRect) const;
		bool tCollision(CRect) const;
		bool offMap(CRect) const;
		bool offMap(CPoint) const;
		int getScreenX(int) const; // accessor method for screen relative x-coordinate
		int getScreenY(int) const; // accessor method for screen relative y-coordinate
		void setSX(int); // mutator method for screen x-coordinate
		void setSY(int); // mutator method for screen y-coordinate
		int getSX() const; // accessor method for screen x-coordinate
		int getSY() const; // accessor method for screen y-coordinate

	private:
		CMovingBitmap map;
		int map_blocks[30][160]; // map blocks 
		int sx, sy; // screen top-left corner coordinates (sx, sy) in map pixel coordinates 
		const int BW = 16, BH = 16; // BW: map block width BH: map block height
		const int MAP_MIN_X = 0, MAP_MAX_X = 2560;
		const int MAP_MIN_Y = 0, MAP_MAX_Y = 480;
	};
}

#endif



