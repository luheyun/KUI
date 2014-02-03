#pragma once

#include "DemoView.h"

class Image;

class PrimitiveView : public DemoView
{
public:
	PrimitiveView();
	virtual ~PrimitiveView();

	void processKeyDown(WPARAM wparam, LPARAM lparam);

protected:
	// DemoView
	virtual bool doDraw(Canvas& canvas) override;

	virtual Image* createBitmap(int width, int height) { return false; }

private:
	void test(Canvas& canvas);
	void testLine(Canvas& canvas);
	void testRect(Canvas& canvas);
	void testClip(Canvas& canvas);
	void testBitmap(Canvas& canvas, Image* bitmap);
    void testAlphaBitmap(Canvas& canvas, Image* bitmap);

protected:
	int _primitiveIndex;
	int _count;
	bool _startTest;
	DWORD _testTime;
};