#pragma once

#include "UIDefine.h"
#include "AnimatorView.h"

class Image;

class SkiaAnimatorView : public AnimatorView
{
public:
    SkiaAnimatorView();
    virtual ~SkiaAnimatorView();

	// AnimatorView
	virtual Image* createImage() override;

private:
};