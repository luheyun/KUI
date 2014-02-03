#pragma once

#include "View.h"

class DemoView : public View
{
public:
	DemoView();
	virtual ~DemoView();

	// View
	virtual bool draw(Canvas& canvas) override;

protected:
	virtual bool doDraw(Canvas& canvas) = 0;
	void showGraphicsType(Canvas& canvas);

protected:
	DWORD _startTime;
};