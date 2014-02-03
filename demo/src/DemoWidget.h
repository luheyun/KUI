#pragma once

#include "UIDefine.h"
#include "widget.h"
#include "SkiaAnimatorView.h"
#include "GdiplusAnimatorView.h"
#include "SkiaView.h"
#include "GdiplusView.h"
#include "GdiView.h"

typedef enum
{
	SKIA_ANIMATE,
	GDIPLUS_ANIMATE,
	SKIA_PRIMITIVE,
	GDIPLUS_PRIMITIVE,
	GDI_PRIMITIVE,
} CurState;

class DemoWidget : public Widget
{
public:
	DemoWidget();
	virtual ~DemoWidget();

	void initialize(int x, int y, int width, int height);
	int getFrameCount() { return _frameCount; }
	void resetFrameCount() { _frameCount = 0; }

protected:
	// Widget
	virtual void drawToWindow();
	virtual LRESULT processKeyDown(WPARAM wparam, LPARAM lparam) override;

private:
	void preState();
	void nextState();

	void startSkiaAnimate();
	void startGdiplusAnimate();

	void endSkiaAnimate();
	void endGdiplusAnimate();

	void startSkiaPrimitive();
	void startGdiPrimitive();
	void startGdiplusPrimitive();

	void endSkiaPrimitive();
	void endGdiPrimitive();
	void endGdiplusPrimitive();

	void clearCurState();

private:
	SkiaAnimatorView _SkiaAnimatorView;
	GdiplusAnimatorView _GdiplusAnimatorView;
	SkiaView _skiaView;
	GdiView _gdiView;
	GdiplusView _gdiplusView;
	CurState _curState;
	int _frameCount;
};