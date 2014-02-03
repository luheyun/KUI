#pragma once

#include "Color.h"

class AK_API KPen
{
public:
	KPen();
    KPen(Color color, int width = 1);
    ~KPen();

	void setColor(Color color);
    Color getColor();
    int getWidth();

private:
    Color _color;
    int _width;
};