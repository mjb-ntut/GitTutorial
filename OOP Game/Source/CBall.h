namespace game_framework {
	/****************** AABB Class Declaration *****************/
	class CGameMap;
	class Monster;

	class CBall
	{
	public:
		CBall();
		//Default Destructor For Now ~CBall();
		bool IsAlive() const;								
		void LoadBitmap(); //load bmp, bmp_center bitmaps
		void OnMove();											
		void OnShow(CGameMap*);											
		void SetXY(int nx, int ny);	//set bmp and bmp_center top-left corner coor.
		void SetVX(int nvx);
		void SetVY(int nvy);
		int GetVX() const;
		int GetVY() const;
		void SetIsAlive(bool alive);							
		void SetDelay(int d);
		bool OffScreen(CGameMap*);
		bool BroadPhase(Monster);
		float TightSweep(Monster);
		list<pair<int, float>> collisions;
	protected:
		CMovingBitmap bmp; //
		CMovingBitmap bmp_center; //bitmap of rotation center  
		int x, y; //bmp top-left corner coordinates (x, y) 
		int vx, vy;
		int dx, dy;	//top-left corner diff. coordinates (dx, dy)
		int index;					// 
		int delay_counter;			// 
		int delay;					// 
		bool is_alive;				//
		
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);
		bool HitRectangle(CRect);
	};
}