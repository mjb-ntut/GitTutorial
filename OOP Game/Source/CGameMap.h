#ifndef CGAMEMAP_H
#define CGAMEMAP_H

namespace game_framework {
	
	class CGameMap
	{
	public:
		CGameMap();
		void LoadBitmap();
		int getScreenX(int) const; // accessor method for screen relative x-coordinate
		int getScreenY(int) const; // accessor method for screen relative y-coordinate
		void setSX(int); // mutator method for screen x-coordinate
		void setSY(int); // mutator method for screen y-coordinate
		int getSX() const; // accessor method for screen x-coordinate
		int getSY() const; // accessor method for screen y-coordinate
		void OnShow();
	private:
		CMovingBitmap map;
		int map_blocks[8][8]; // map blocks 
		int sx, sy; // screen top-left corner coordinates (sx, sy) in map pixel coordinates 
		const int BW, BH; // BW: map block width BH: map block height
	};
}

#endif



