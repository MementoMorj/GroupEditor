#include "Circle.h"

namespace Shapes
{
    std::wstring Circle::getType() const
    {
        return L"Circle";
    }

    std::wstring Circle::display() const
    {
        return getType() +
            L"(" +
            std::to_wstring(x) + L"," +
            std::to_wstring(y) + L"," +
            std::to_wstring(r) +
            L")";
    }

    std::pair<int, int> Circle::getSize() const
    {
        int d = r * 2;
        return std::make_pair(x + d, y + d);
    }

    int Circle::getX() const
    {
        return x;
    }

    int Circle::getY() const
    {
        return y;
    }

    int Circle::getR() const
    {
        return r;
    }

    bool Circle::setX(int x)
    {
        if (x < 0)
        {
            return false;
        }
        this->x = x;
        return true;
    }

    bool Circle::setY(int y)
    {
        if (y < 0)
        {
            return false;
        }
        this->y = y;
        return true;
    }

    bool Circle::setR(int r)
    {
        if (r < 0)
        {
            return false;
        }
        this->r = r;
        return true;
    }

    std::wistream& operator>>(std::wistream& in, Circle& circle)
    {
        std::wstring chunk;
        getline(in, chunk, L'(');
        getline(in, chunk, L',');
        circle.setX(std::stoi(chunk));
        getline(in, chunk, L',');
        circle.setY(std::stoi(chunk));
        getline(in, chunk, L')');
        circle.setR(std::stoi(chunk));
        return in;
    }
};


