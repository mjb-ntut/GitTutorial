/*
 * gamelib.h: 
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *		1. Add ENABLE_AUDIO flag.
 *   2004-03-02 V4.0
 *		1. Add CInteger class.
 *      2. Add CGameState abstract class and adjust CGame to apply
 *         state pattern for switching game states.
 *   2004-03-08 V4.1
 *      1. Add OPEN_AS_FULLSCREEN flag.
 *      2. The Game Engine now becomes a framework.
 *   2005-07-28
 *      1. Add GAME_ASSERT macro to display run time errors gracefully.
 *      2. Remove CDDarw::CheckSystem(). It is useless.
 *   2005-09-08
 *      1. Eliminate CSpecialEffect::Abort. It is useless now.
 *      2. Add SHOW_GAME_CYCLE_TIME flag.
 *      3. Add DEFAULT_BG_COLOR flag;
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add MOUSEMOVE Handler for CGame and CGameState.
 *      2. Add _TRACE preprocessor flag for VC++.net.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Remove constantness of CAnimation::DELAY_COUNT.
 *      3. Enhance CAnimation to support SetDelayCount(), Reset(), and IsFinalBitmap().
 *      4. Remove CAnimation::GetLocation() and CMovingBitmap::GetLocation().
 *      5. Bitmap coordinate can no longer be set by CMovingBitmap::LoadBitmap().
 *         Defauts to (0,0).
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *      2. Fix bug: audio is now correctly recovered after a sleep or suspension of windows.
 *      3. Support ENABLE_GAME_PAUSE.
 *   2008-02-15 V4.4
 *      1. Add setup project for Visual studio 2005.
 *      2. Support bitmap scaling when ShowBitmap(scale) is called.
 *      3. Add namespace game_framework.
 *      4. Make the class CGame a singleton so that MFC can access it easily.
 *      5. Support loading of bitmap from bmp file.
 *      6. Support ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Rewrite CAudio with MCI commands to eliminate dependency with DirectMusic.
*/

/////////////////////////////////////////////////////////////////////////////
// �w�q�C���i�]�w�����һP����
/////////////////////////////////////////////////////////////////////////////

#define SIZE_X				 640		// Default Screen Width
#define SIZE_Y				 480		// Default Screen Height
#define OPEN_AS_FULLSCREEN	 false		// �O�_�H���ù��覡�}�ҹC��
#define SHOW_LOAD_PROGRESS   true		// �O�_���loading(OnInit)���i��
#define DEFAULT_BG_COLOR	 RGB(0,0,0)	// Default Background Color
#define GAME_CYCLE_TIME		 33		    // �C33ms�]�@��Move��Show(�C��30��)
#define SHOW_GAME_CYCLE_TIME false		// �O�_�bdebug mode���cycle time
#define ENABLE_GAME_PAUSE	 true		// �O�_���\�H Ctrl-Q �Ȱ��C��
#define ENABLE_AUDIO		 true		// �Ұʭ��Ĥ���


/****************** GAME_STATES Constants Declaration *****************/
enum GAME_STATES {
	GAME_STATE_INIT,
	GAME_STATE_RUN,
	GAME_STATE_OVER
};

/****************** STL Library Header *****************/
#include <list>
#include <vector>
#include <map>
using namespace std;

/****************** GAME_ASSERT Macro Header *****************/
#define GAME_ASSERT(boolexp,str)											\
		if (!(boolexp)) {													\
			int id;															\
			char s[300]="";													\
			sprintf(s,"Game fatal error:\n\n%s\n\nFile: %s\n\nLine: %d"		\
				"\n\n(Press Retry to debug the application, "				\
				"if it is executed in debug mode.)"							\
				"\n(Press Cancel otherwise.)",								\
				 str , __FILE__,__LINE__);									\
			id = AfxMessageBox(s, MB_RETRYCANCEL);							\
			if (id == IDCANCEL)												\
				exit(1);													\
			AfxDebugBreak();												\
		}

namespace game_framework {

	/****************** CSpecialEffect Class Declaration *****************/
	class CSpecialEffect {
	public:
		static void  SetCurrentTime();					// �x�s�ثe���ɶ���ctime
		static DWORD GetEllipseTime();					// Ū���ثe���ɶ� - ctime
		static int   GetCurrentTimeCount();				// Ū���x�sctime������
		static void  Delay(DWORD ms);					// ���� x ms
		static void  DelayFromSetCurrentTime(DWORD ms);	// ��ctime�_��A���� x ms
	private:
		static DWORD ctime;
		static int	 ctimeCount;
	};

	/****************** CDDraw Class Declaration *****************/
	class CDDraw {
		friend class CMovingBitmap;
	public:
		~CDDraw();
		static void  BltBackColor(DWORD);		// �NBack plain�����ۤW���w���C��
		static void  BltBackToPrimary();		// �NBack plain�K��Primary plain
		static CDC*  GetBackCDC();				// ���oBack Plain��DC (device context)
		static void  GetClientRect(CRect &r);	// ���o�]�w���ѪR��
		static void  Init(int, int);			// Initialize direct draw
		static void  ReleaseBackCDC();			// ��Back Plain��DC (device context)
		static bool  SetFullScreen(bool);		// �]�w�����ù��Ҧ�/�����Ҧ�
		static bool  IsFullScreen();			// �^���O�_�����ù��Ҧ�/�����Ҧ�
	private:
		CDDraw();								// private constructor
		static void  BltBitmapToBack(unsigned SurfaceID, int x, int y);
		static void  BltBitmapToBack(unsigned SurfaceID, int x, int y, double factor);
		static void  BltBitmapToBitmap(unsigned SourceID, unsigned TargetID, int x, int y);
		static void	 CheckDDFail(char *s);
		static bool  CreateSurface();
		static bool  CreateSurfaceFullScreen();
		static bool  CreateSurfaceWindowed();
		static void  LoadBitmap(int i, int IDB_BITMAP);
		static void  LoadBitmap(int i, char *filename);
		static DWORD MatchColorKey(LPDIRECTDRAWSURFACE lpDDSurface, COLORREF color);
		static int   RegisterBitmap(int IDB_BITMAP, COLORREF ColorKey);
		static int   RegisterBitmap(char *filename, COLORREF ColorKey);
		static void  ReleaseSurface();
		static void  RestoreSurface();
		static void  SetColorKey(unsigned SurfaceID, COLORREF color);
		static HDC					hdc;
		static CDC					cdc;
		static CView				*pCView;
		static LPDIRECTDRAW2		lpDD;
		static LPDIRECTDRAWCLIPPER	lpClipperPrimary;
		static LPDIRECTDRAWCLIPPER	lpClipperBack;
		static LPDIRECTDRAWSURFACE	lpDDSPrimary;
		static LPDIRECTDRAWSURFACE	lpDDSBack;
		static vector<LPDIRECTDRAWSURFACE>	lpDDS;
		static HRESULT				ddrval;
		static vector<int>			BitmapID;
		static vector<string>		BitmapName;
		static vector<CRect>		BitmapRect;
		static vector<COLORREF>		BitmapColorKey;
		static bool					fullscreen;
		static CDDraw				ddraw;
		static int					size_x, size_y;
	};

	/****************** CMovingBitmap Class Declaration *****************/
	class CMovingBitmap {
	public:
		CMovingBitmap();
		int   Height();						// accessor bitmap height
		int   Width();						// accessor bitmap width
		int   Left();						// accessor Bitmap top-left corner x-coordinate
		int   Top();						// accessor bitmap top-left corner y-coordinate
		void  LoadBitmap(int, COLORREF = CLR_INVALID);		// 
		void  LoadBitmap(char *, COLORREF = CLR_INVALID);	// 
		void  SetTopLeft(int, int);			// mutator top-left corner coordinate (x,y)
		void  ShowBitmap();					// display bitmap
		void  ShowBitmap(double factor);	// 
		void  ShowBitmap(CMovingBitmap &);	// 

	//protected:
		CRect    location;			// location of the bitmap
		bool     isBitmapLoaded;	// whether a bitmap has been loaded
		unsigned SurfaceID;			// the surface id of this bitmap
	};

	/****************** CAnimation Class Declaration *****************/
	class CAnimation {
	public:
		CAnimation(int = 10);				// Constructor
		void  AddBitmap(int, COLORREF = CLR_INVALID);
		void  AddBitmap(char *, COLORREF = CLR_INVALID);
		int   GetCurrentBitmapNumber();	// 
		int   Height();					//
		bool  IsFinalBitmap();			//
		int   Left();					// 
		void  OnMove();					// 
		void  OnShow();					// 
		void  Reset();					// 
		void  SetDelayCount(int);		// 
		void  SetTopLeft(int, int);		// 
		int   Top();					// 
		int   Width();					//
	private:
		list<CMovingBitmap>				bmp;			// CMovingBitmap List
		list<CMovingBitmap>::iterator	bmp_iter;		// CMovingBitmap List Iterator
		int								bmp_counter;	// Current Index of CCMovingBitmap List
		int								delay_counter;	// 
		int								delay_count;	// 
		int								x, y;			// 
	};

	/****************** CInteger Class Declaration *****************/
	class CInteger {
	public:
		CInteger(int = 5);			// default 5 digits
		void Add(int n);			// �W�[��ƭ�
		int  GetInteger();			// �^�Ǿ�ƭ�
		void LoadBitmap();			// ���J0..9�έt�����ϧ�
		void SetInteger(int);		// �]�w��ƭ�
		void SetTopLeft(int, int);	// �N�ʵe�����W���y�в��� (x,y)
		void ShowBitmap();			// �N�ʵe�K��ù�
	private:
		const int NUMDIGITS;			// �@���NUMDIGITS�Ӧ��
		static CMovingBitmap digit[11]; // �x�s0..9�έt�����ϧ�(bitmap)
		int x, y;						// ��ܪ��y��
		int n;							// ��ƭ�
		bool isBmpLoaded;				// �O�_�w�g���J�ϧ�
	};

	/****************** CGameState Class Forward Declarations *****************/
	class CGame;
	class CGameStateInit;
	class CGameStateRun;
	class CGameStateOver;

	/****************** CGameState Class Declaration *****************/
	class CGameState {
	public:
		CGameState(CGame *g);
		void OnDraw();			// Template Method
		void OnCycle();			// Template Method
		virtual ~CGameState() {}								// virtual destructor
		virtual void OnBeginState() {}							// �]�w�C���i�J�o�Ӫ��A�ɩһݪ����
		virtual void OnInit() {}								// ���A����Ȥιϧγ]�w
		virtual void OnKeyDown(UINT, UINT, UINT) {}				// �B�z��LDown���ʧ@
		virtual void OnKeyUp(UINT, UINT, UINT) {}				// �B�z��LUp���ʧ@
		virtual void OnLButtonDown(UINT nFlags, CPoint point) {}// �B�z�ƹ����ʧ@
		virtual void OnLButtonUp(UINT nFlags, CPoint point) {}	// �B�z�ƹ����ʧ@
		virtual void OnMouseMove(UINT nFlags, CPoint point) {}  // �B�z�ƹ����ʧ@ 
		virtual void OnRButtonDown(UINT nFlags, CPoint point) {}// �B�z�ƹ����ʧ@
		virtual void OnRButtonUp(UINT nFlags, CPoint point) {}	// �B�z�ƹ����ʧ@
	protected:
		void GotoGameState(int state);							// ���D�ܫ��w��state
		void ShowInitProgress(int percent);						//
																//
																// Pure Virtual Functions
		virtual void OnMove() {}								// ���ʳo�Ӫ��A���C������
		virtual void OnShow() = 0;								// ��ܳo�Ӫ��A���C���e��
		CGame *game;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class�O�C�����֤ߡA����C�����i��
	// �@�몺�C���ä��ݪ����ާ@�o�Ӫ���A�]���i�H���޳o��class���ϥΤ�k
	/////////////////////////////////////////////////////////////////////////////

	class CGame {
	public:
		CGame();										// Constructor
		~CGame();										// Destructor
		bool IsRunning();								// Ū���C���O�_���b�i�椤
		void OnDraw();									// ����CGameView��OnDraw()
		void OnFilePause();								// �C���Ȱ�
		void OnInit();									// �C��ø�Ϥέ��Ī���l��
		void OnInitStates();							// �C���U���A����Ȥιϧγ]�w
		bool OnIdle();									// �C�����D�j��
		void OnKeyDown(UINT, UINT, UINT);				// �B�z��LDown���ʧ@
		void OnKeyUp(UINT, UINT, UINT);					// �B�z��LUp���ʧ@
		void OnKillFocus();								// �C���Q���Ȱ�
		void OnLButtonDown(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);    // �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnResume();								// �B�z�ۡu�ݩR�v�٭쪺�ʧ@
		void OnSetFocus();								// �B�zFocus
		void OnSuspend();								// �B�z�u�ݩR�v���ʧ@
		void SetGameState(int);
		static CGame *Instance();
	private:
		bool			running;			// �C���O�_���b�i�椤(���QPause)
		bool            suspended;			// �C���O�_�Qsuspended
		const int		NUM_GAME_STATES;	// �C�������A��(3�Ӫ��A)
		CGameState		*gameState;			// pointer���V�ثe���C�����A
		CGameState		*gameStateTable[3];	// �C�����A����pointer
		static CGame	instance;			// �C���ߤ@��instance
	};

}