#include "Color.h"

Color::Color()
    : _color(0xFF000000)
{
    
}

Color::Color(byte a, byte r, byte g, byte b)
{
    _color = (a << 24) | (r << 16) |  + (g << 8) + (b << 0);
}

Color::~Color()
{

}

void Color::setValue(int argb)
{
    _color = argb;
}

int Color::getValue() const
{
    return _color;
}

byte Color::getA()
{
	return _color >> 24;
}

byte Color::getR()
{
	return (_color & 0x00FF0000) >> 16;
}

byte Color::getG()
{
	return (_color & 0x0000FF00) >> 8;
}

byte Color::getB()
{
	return _color & 0x000000FF;
}