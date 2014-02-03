#pragma once

#include "Brush.h"
#include "Color.h"

class SolidBrush : public KBrush
{
public:
	SolidBrush(const Color& color);
	virtual ~SolidBrush();

	// GBrush
	virtual UI_ENUM::BrushType getBrushType() override;

	// SolidBrush
	Color getColor() const;
	void setColor(const Color& color);

private:
	Color _color;
};