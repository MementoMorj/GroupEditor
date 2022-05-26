#pragma once
#include "Shape.h"
#include <iostream>

namespace Shapes {
    class Rectangle :
        public Shape
    {
    private:
        int x, y, w, h;
    public:

        std::wstring getType() const override;
        std::wstring display() const override;
        std::pair<int, int> getSize() const override;

        int getX() const;
        int getY() const;
        int getW() const;
        int getH() const;

        bool setX(int x);
        bool setY(int y);
        bool setW(int w);
        bool setH(int h);
    };

    std::wistream& operator>>(std::wistream& in, Rectangle& rectangle);
}


