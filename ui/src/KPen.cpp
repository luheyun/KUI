#include "KPen.h"

KPen::KPen()
	: _color(Color(0, 0, 0, 0))
{

}

KPen::KPen(Color color, int width)
    : _color(color)
    , _width(width)
{

}

KPen::~KPen()
{

}

void KPen::setColor(Color color)
{
	_color = color;
}

Color KPen::getColor()
{
    return _color;
}

int KPen::getWidth()
{
    return _width;
}


