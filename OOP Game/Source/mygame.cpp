/*
 * mygame.cpp: Game Class Implementation
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
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <stdio.h>

namespace game_framework 
{
	/****************** GameStateInit Class Definition *****************/
	CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
	{}

	void CGameStateInit::OnInit()
	{
		ShowInitProgress(0);	// Display Loading Bar. Parameter Percentage Loaded
		logo.LoadBitmap(IDB_BACKGROUND2);	// Loads Game Logo Bitmap
		Sleep(300);	//
	}

	void CGameStateInit::OnBeginState()
	{}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_SPACE = ' ';
		if (nChar == KEY_SPACE)
			GotoGameState(GAME_STATE_RUN);						
		else if (nChar == KEY_ESC)								
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		GotoGameState(GAME_STATE_RUN);
	}

	void CGameStateInit::OnShow()
	{
		//Set Top-Left Corner of Game Logo & Display
		logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);	
		logo.ShowBitmap();
		
		//
		CDC *pDC = CDDraw::GetBackCDC();		 
		CFont f,*fp;
		f.CreatePointFont(160,"Times New Roman");	
		fp=pDC->SelectObject(&f);					
		pDC->SetBkColor(RGB(0,0,0));
		pDC->SetTextColor(RGB(255,255,0));
		pDC->TextOut(80,320,"Click mouse or press SPACE to begin.");
		pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
		if (ENABLE_GAME_PAUSE)
			pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
		pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
		pDC->SelectObject(fp);						
		CDDraw::ReleaseBackCDC();					
	}								

	/****************** GameStateOver Class Definition *****************/
	CGameStateOver::CGameStateOver(CGame *g) : CGameState(g)
	{}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}

	void CGameStateOver::OnInit()
	{
		//
		ShowInitProgress(66);	
		//
		//
		Sleep(300);			
		//
		//
		ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{
		CDC *pDC = CDDraw::GetBackCDC();			
		CFont f,*fp;
		f.CreatePointFont(160,"Times New Roman");	
		fp=pDC->SelectObject(&f);					
		pDC->SetBkColor(RGB(0,0,0));
		pDC->SetTextColor(RGB(255,255,0));
		char str[80];								
		sprintf(str, "Game Over ! (%d)", counter / 30);
		pDC->TextOut(240,210,str);
		pDC->SelectObject(fp);					
		CDDraw::ReleaseBackCDC();					
	}

	/****************** GameStateRun Class Definition *****************/
	CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
	{}

	CGameStateRun::~CGameStateRun()
	{}

	void CGameStateRun::OnBeginState()
	{
		const int BACKGROUND_X = 60;
		const int ANIMATION_SPEED = 15;
					
		help.SetTopLeft(0, SIZE_Y - help.Height());	
		
		//
		gamemap.setSX(0);
		gamemap.setSY(0);
		//
		hero.SetTopLeft(60, 240);
		//CAudio::Instance()->Play(AUDIO_LAKE, true);		
		
	}

	void CGameStateRun::OnMove()
	{
		//Example of Game Cursor If Neeeded
		//SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
		
		//AABB OnMove
		hero.OnMove(&gamemap);
		for (auto i = ball_list.begin(); i != ball_list.end(); i++)
			i->OnMove();
		//Example of Switching Game States
		//if (hits_left.GetInteger() <= 0) 	
		//GotoGameState(GAME_STATE_OVER);
	}

	void CGameStateRun::OnInit()
	{
		
		ShowInitProgress(33);	// Display Initialization Progress at 33%
		gamemap.LoadBitmap();
		hero.LoadBitmap();
		//
		ShowInitProgress(50);	// Display Initialization Progress at 50%
		Sleep(300); 
		
		help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));	
		
		//Load Audio Instance (Example)
		//CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");
		
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 37;
		const char KEY_UP = 38;	
		const char KEY_RIGHT = 39; 
		const char KEY_DOWN = 40;
		const char KEY_SPACE = ' ';
		if (nChar == KEY_LEFT)
		{
			TRACE("KEY_LEFT DOWN\n");
			hero.setVX(-4.f);
		}
			
		if (nChar == KEY_RIGHT)
		{
			TRACE("KEY_RIGHT DOWN\n");
			hero.setVX(4.f);
		}	
		if (nChar == KEY_UP)
			hero.setVY(0.f);
		if (nChar == KEY_DOWN)
			hero.setVY(1.f);
		if (nChar == KEY_SPACE)
		{
			TRACE("KEY_SPACE DOWN\n");
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 37;
		const char KEY_UP = 38;
		const char KEY_RIGHT = 39;
		const char KEY_DOWN = 40;
		const char KEY_SPACE = ' ';
		if (nChar == KEY_LEFT)
			hero.setVX(0.f);
		if (nChar == KEY_RIGHT)
			hero.setVX(0.f);
		if (nChar == KEY_UP)
			hero.setVY(0.f);
		if (nChar == KEY_DOWN)
			hero.setVY(0.f);
		if (nChar == KEY_SPACE)
		{
			//Initialize AABB Velocity (vx, vy)
			TRACE("KEY_SPACE_UP\n");
			//hero.setVX(0.f);
			hero.setVY(-15.f);
		}
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)
	{
		//eraser.SetMovingLeft(true);
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)
	{
		//eraser.SetMovingLeft(false);
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)
	{}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 
	{
		//eraser.SetMovingRight(true);
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	//
	{
		//eraser.SetMovingRight(false);
	}

	void CGameStateRun::OnShow()
	{
		gamemap.OnShow();
		//Show Hero BitMap
		hero.OnShow(&gamemap);

		for (auto i = ball_list.begin(); i != ball_list.end(); i++)
			i->OnShow(&gamemap);
		//hero.setVX(0.f);
		//hero.setVY(0.f);
	}

} //namespace game_framework

