#include "CGameMap.h"

namespace game_framework {
	/****************** CEraser Class Declaration *****************/
	class CEraser
	{
	public:
		CEraser();
		int  GetX1();					// top-left corner x-coordinate
		int  GetY1();					// top-left corner y-coordinate
		int  GetX2();					// bottom-right corner x-coordinate
		int  GetY2();					// bottom-right corner y-coordinate
		void Initialize();				// sets init. pos. & sets all isMoving to false 
		void LoadBitmap();				// 
		void OnMove();					// 
		void OnShow();					// 
		void SetMovingDown(bool flag);	// isMovingDown accessor function
		void SetMovingLeft(bool flag);	// isMovingLeft accessor function
		void SetMovingRight(bool flag); // isMovingRight accessor function
		void SetMovingUp(bool flag);	// isMovingUp accessor function
		void SetXY(int nx, int ny);		// set top-left corner to (nx, ny)
	protected:
		CAnimation animation;		// CAnimation Object
		int x, y;					// Top-Left Corner Coordinate
		bool isMovingDown;			// Moving Down? (T/F)
		bool isMovingLeft;			// Moving Left? (T/F)
		bool isMovingRight;			// Moving Right? (T/F)
		bool isMovingUp;			// Moving Up? (T/F)
	};
}