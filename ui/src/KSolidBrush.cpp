#include "UIDefine.h"
#include "KSolidBrush.h"

KSolidBrush::KSolidBrush(const Color& color)
	: _color(color)
{

}

KSolidBrush::~KSolidBrush()
{

}

ak::BrushType KSolidBrush::getBrushType()
{
	return ak::SolidBrush;
}

Color KSolidBrush::getColor() const
{
	return _color;
}

void KSolidBrush::setColor(const Color& color)
{
	_color = color;
}