#include "Pen.h"

Pen::Pen(Color color, int width)
    : _color(color)
    , _width(width)
{

}

Pen::~Pen()
{

}

Color Pen::getColor()
{
    return _color;
}

int Pen::getWidth()
{
    return _width;
}


