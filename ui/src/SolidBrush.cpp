#include "UIDefine.h"
#include "SolidBrush.h"

SolidBrush::SolidBrush(const Color& color)
	: _color(color)
{

}

SolidBrush::~SolidBrush()
{

}

UI_ENUM::BrushType SolidBrush::getBrushType()
{
	return UI_ENUM::SolidBrush;
}

Color SolidBrush::getColor() const
{
	return _color;
}

void SolidBrush::setColor(const Color& color)
{
	_color = color;
}