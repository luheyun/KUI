#pragma once

#include "Color.h"

class AK_API Pen
{
public:
    Pen(Color color, int width = 1);
    ~Pen();

    Color getColor();
    int getWidth();

private:
    Color _color;
    int _width;
};