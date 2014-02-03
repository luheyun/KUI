#pragma once

#include "UIDefine.h"
#include "DemoView.h"

class Image;
class KPoint;

class AnimatorView : public DemoView
{
public:
	AnimatorView();
	virtual ~AnimatorView();

	// View
	virtual bool init() override;

	// DemoView
	virtual bool doDraw(Canvas& canvas) override;

protected:
	virtual Image* createImage() = 0;

protected:
	Image* _imageQQ;
	int _alpha;
	float _degrees;
	Image* _imageFlower;
};