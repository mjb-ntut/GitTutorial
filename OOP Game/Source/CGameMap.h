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
		bool isEmptyH(int, int, int) const;
		bool isEmptyV(int, int, int) const;
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
		int map_blocks[15][58]; // map blocks 
		int sx, sy; // screen top-left corner coordinates (sx, sy) in map pixel coordinates 
		const int BW = 32, BH = 32; // BW: map block width BH: map block height
		const int MAP_MIN_X = 0, MAP_MAX_X = 1856;
		const int MAP_MIN_Y = 0, MAP_MAX_Y = 480;
	};
}

#endif



