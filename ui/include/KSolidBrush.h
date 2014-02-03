#pragma once

#include "Brush.h"
#include "Color.h"

class KSolidBrush : public KBrush
{
public:
	KSolidBrush(const Color& color);
	virtual ~KSolidBrush();

	// KBrush
	virtual ak::BrushType getBrushType() override;

	// SolidBrush
	Color getColor() const;
	void setColor(const Color& color);

private:
	Color _color;
};