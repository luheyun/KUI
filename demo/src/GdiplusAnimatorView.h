#pragma once

#include "UIDefine.h"
#include "AnimatorView.h"

class Image;

class GdiplusAnimatorView : public AnimatorView
{
public:
	GdiplusAnimatorView();
	virtual ~GdiplusAnimatorView();

protected:
	// AnimatorView
	virtual Image* createImage();

private:
};