namespace game_framework {
	/****************** AABB Class Declaration *****************/
	class CGameMap;
	class CBall
	{
	public:
		CBall();
		bool IsAlive();								
		void LoadBitmap(); //load bmp, bmp_center bitmaps
		void OnMove();											
		void OnShow(CGameMap*);											
		void SetXY(int nx, int ny);	//set bmp and bmp_center top-left corner coor.
		void SetIsAlive(bool alive);							
		void SetDelay(int d);
	protected:
		CMovingBitmap bmp; //
		CMovingBitmap bmp_center; //bitmap of rotation center  
		int x, y; //bmp top-left corner coordinates (x, y) 
		int dx, dy;	//top-left corner diff. coordinates (dx, dy)
		int index;					// 
		int delay_counter;			// 
		int delay;					// 
		bool is_alive;				//
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	
	};
}