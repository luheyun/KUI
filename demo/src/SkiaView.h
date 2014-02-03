#pragma once

#include "PrimitiveView.h"

class SkiaView : public PrimitiveView
{
public:
	SkiaView();
	virtual ~SkiaView();

protected:
	virtual Image* createBitmap(int width, int height) override;
};