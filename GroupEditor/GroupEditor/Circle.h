#pragma once
#include "Shape.h"
#include <iostream>

namespace Shapes {
	class Circle :
		public Shape
	{
	private:
		int x;
		int y;
		int r;
	public:

		std::wstring getType() const override;
		std::wstring display() const override;
		std::pair<int, int> getSize() const override;

		int getX() const;
		int getY() const;
		int getR() const;

		bool setX(int x);
		bool setY(int y);
		bool setR(int r);
	};

	std::wistream& operator>>(std::wistream& in, Circle& circle);
}
