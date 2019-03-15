namespace game_framework {
	/****************** CBouncingBall Class Declaration *****************/
	class CBouncingBall
	{
	public:
		CBouncingBall();
		void LoadBitmap();		// 
		void OnMove();			// 
		void OnShow();			// 
		void Jump(); //
	private:
		pair<int, int> location; // 
		pair<int, int> velocity; //
		pair<int, int> acceleration; //
		pair<int, int> jerk; //
		const int FLOOR;		// 
		CAnimation animation;	// 
	};
}