#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace game_framework {
	/****************** Rectangle Class Declaration *****************/
	class Rectangle
	{
	public:
		Rectangle();
		Rectangle(int, int, int, int);
		int getX() const;
		int getY() const;
		void setX(int);
		void setY(int);
		int getWidth() const;
		int getHeight() const;
		void setWidth(int);
		void setHeight(int);
		bool isOverlap(Rectangle);
	//private:
		int x, y;
		int width, height;
	};
}

#endif