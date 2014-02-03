#pragma once

#include "PrimitiveView.h"

class GdiplusView : public PrimitiveView
{
public:
	GdiplusView();
	virtual ~GdiplusView();

protected:
	virtual Image* createBitmap(int width, int height);
};