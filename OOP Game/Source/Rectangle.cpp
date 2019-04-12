#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Rectangle.h"

namespace game_framework {
	/****************** Rectangle Class Definition *****************/
	Rectangle::Rectangle() : x(0), y(0), width(16), height(16)
	{}

	Rectangle::Rectangle(int nx, int ny, int nwidth, int nheight) :
		x(nx), y(nx), width(nwidth), height(nheight)
	{}

	int Rectangle::getX() const
	{
		return x;
	}

	int Rectangle::getY() const
	{
		return y;
	}

	void Rectangle::setX(int nx)
	{
		x = nx;
	}

	void Rectangle::setY(int ny)
	{
		y = ny;
	}

	int Rectangle::getWidth() const
	{
		return width;
	}

	int Rectangle::getHeight() const
	{
		return height;
	}

	void Rectangle::setWidth(int nwidth)
	{
		width = nwidth;
	}

	void Rectangle::setHeight(int nheight)
	{
		height = nheight;
	}

	bool Rectangle::isOverlap(Rectangle r2)
	{
		if (x + width < r2.x || x > r2.x + r2.width || y + height < r2.y || y > r2.y + r2.height)
			return false;
		else
			return true;
	}
}