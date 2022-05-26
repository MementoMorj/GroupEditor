#pragma once
#include <vector>
#include "Shape.h"
#include <iostream>

class Group
{
private:
	std::vector<Group> groups;
	std::vector<Shapes::Shape*> shapes;

	int x;
	int y;
	int w;
	int h;

public:
	Group();
	Group(int x, int y, int w, int h);

	std::wstring display() const
	{
		return std::wstring(L"Group") +
			L"(" +
			std::to_wstring(x) + L"," +
			std::to_wstring(y) + L"," +
			std::to_wstring(w) + L"," +
			std::to_wstring(h) +
			L")";
	}

	int getX() const;
	int getY() const;
	int getW() const;
	int getH() const;

	bool setX(int x);
	bool setY(int y);
	bool setW(int w);
	bool setH(int h);

	bool add(const Group& group)
	{
		if ((group.getX() + group.getW() > w) || (group.getY() + group.getH() > h))
		{
			return false;
		}
		groups.push_back(group);
		return true;
	}

	bool add(Shapes::Shape* shape)
	{
		std::pair<int, int> size = shape->getSize();
		printf("%d %d\n", size.first > w, size.second > h);
		if ((size.first > w) + (size.second > h))
		{
			return false;
		}
		shapes.push_back(shape);
		return true;
	}

	bool del(int i)
	{
		if (i < 1)
		{
			return false;
		}
		i -= 1;
		if (i < groups.size())
		{
			groups.erase(groups.begin() + i);
			return true;
		}
		i -= (int)(groups.size());
		if (i > shapes.size())
		{
			return false;
		}
		shapes.erase(shapes.begin() + i);
		return true;
	}

	const std::vector<Group>* getGroups() const
	{
		return &groups;
	}

	const std::vector<Shapes::Shape*>* getShapes() const
	{
		return &shapes;
	}

	Group* getGroup(int i)
	{
		return &groups[i];
	}

	Shapes::Shape** getShape(int i)
	{
		return &shapes[i];
	}
};

std::wistream& operator>>(std::wistream& in, Group& group);