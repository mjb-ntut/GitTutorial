#include "stdafx.h"
#include "CMovingRect.h"

namespace game_framework
{
	CMovingRect::CMovingRect()
	{}

	CMovingRect::CMovingRect(const CRect& r, pair<int, int> v, pair<int, int> a)
		: bRect(r), vel(v), acc(a)
	{}

	CMovingRect::~CMovingRect()
	{}

	pair<int, int> CMovingRect::getVel() const
	{
		return vel;
	}

	

	void CMovingRect::UpdatePos(CMovingRect& r, float t)
	{
		pair<int, int> ds = FindDis(t);
		r.MoveToXY(r.left + ds.first, r.right + ds.second);
		return;
	}
	
	bool RectOverlap(const CRect& r1, const CRect& r2)
	{
		return (r1.left <= r2.right && r1.right >= r2.left
			&& r1.top <= r2.bottom && r1.bottom >= r2.top);
	}

	pair<int, int> CMovingRect::FindDis(float t) const
	{
		float ndx = vel.first * t + 0.5f * acc.first * powf(t, 2.f);
		if (vel.first < 0)
			ndx = ceilf(ndx);
		else
			ndx = floorf(ndx);

		float ndy = vel.second * t + 0.5f * acc.second * powf(t, 2.f);
		if (vel.second < 0)
			ndy = ceilf(ndy);
		else
			ndy = floorf(ndy);

		return pair<int, int>(static_cast<int>(ndx), static_cast<int>(ndy));
	}

	CRect CMovingRect::DestRect(float t) const
	{
		pair<int, int> ds = FindDis(t);
		CRect destRect(bRect);
		destRect.MoveToXY(bRect.left + ds.first, bRect.right + ds.second);
		return destRect;
	}
}
