#include "Group.h"

Group::Group(int x, int y, int w, int h)
{
	setX(x);
	setY(y);
	setW(w);
	setH(h);
}

Group::Group() :
	Group(0, 0, 0, 0)
{

}

int Group::getX() const
{
	return x;
}

int Group::getY() const
{
	return y;
}

int Group::getW() const
{
	return w;
}

int Group::getH() const
{
	return h;
}

bool Group::setX(int x)
{
	if (x < 0)
	{
		return false;
	}
	this->x = x;
	return true;
}

bool Group::setY(int y)
{
	if (y < 0)
	{
		return true;
	}
	this->y = y;
	return false;
}

bool Group::setW(int w)
{
	if (w < 0)
	{
		return false;
	}
	this->w = w;
	return true;
}

bool Group::setH(int h)
{
	if (h < 0)
	{
		return false;
	}
	this->h = h;
	return true;
}

std::wistream& operator>>(std::wistream& in, Group& group)
{
	std::wstring chunk;
	getline(in, chunk, L'(');
	getline(in, chunk, L',');
	group.setX(std::stoi(chunk));
	getline(in, chunk, L',');
	group.setY(std::stoi(chunk));
	getline(in, chunk, L',');
	group.setW(std::stoi(chunk));
	getline(in, chunk, L')');
	group.setH(std::stoi(chunk));
	return in;
}
