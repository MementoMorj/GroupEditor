#include "Rectangle.h"

namespace Shapes {
	std::wstring Rectangle::getType() const
	{
		return L"Rectangle";
	}

	std::wstring Rectangle::display() const
	{
		return getType() +
			L"(" +
			std::to_wstring(x) + L"," +
			std::to_wstring(y) + L"," +
			std::to_wstring(w) + L"," +
			std::to_wstring(h) +
			L")";
	}

	std::pair<int, int> Rectangle::getSize() const
	{
		return std::make_pair(x + w, y + h);
	}

	int Rectangle::getX() const
	{
		return x;
	}

	int Rectangle::getY() const
	{
		return y;
	}

	int Rectangle::getW() const
	{
		return w;
	}

	int Rectangle::getH() const
	{
		return h;
	}

	bool Rectangle::setX(int x)
	{
		if (x < 0)
		{
			return false;
		}
		this->x = x;
		return true;
	}

	bool Rectangle::setY(int y)
	{
		if (y < 0)
		{
			return false;
		}
		this->y = y;
		return true;
	}

	bool Rectangle::setW(int w)
	{
		if (w < 0)
		{
			return false;
		}
		this->w = w;
		return true;
	}

	bool Rectangle::setH(int h)
	{
		if (h < 0)
		{
			return false;
		}
		this->h = h;
		return true;
	}

	std::wistream& operator>>(std::wistream& in, Rectangle& rectangle)
	{
		std::wstring chunk;
		getline(in, chunk, L'(');
		getline(in, chunk, L',');
		rectangle.setX(std::stoi(chunk));
		getline(in, chunk, L',');
		rectangle.setY(std::stoi(chunk));
		getline(in, chunk, L',');
		rectangle.setW(std::stoi(chunk));
		getline(in, chunk, L')');
		rectangle.setH(std::stoi(chunk));
		return in;
	}
}


