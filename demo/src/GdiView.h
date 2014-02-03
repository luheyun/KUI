#pragma once

#include "PrimitiveView.h"

class GdiView : public PrimitiveView
{
public:
	GdiView();
	virtual ~GdiView();

	// view
	virtual bool draw(Canvas& canvas) override;

    virtual Image* createBitmap(int width, int height) override;
};