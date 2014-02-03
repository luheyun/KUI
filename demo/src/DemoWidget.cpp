#include "Stdafx.h"
#include "DemoWidget.h"

extern HINSTANCE g_hInst;

DemoWidget::DemoWidget()
	: _curState(SKIA_ANIMATE)
	, _frameCount(0)
{
}

DemoWidget::~DemoWidget()
{

}

void DemoWidget::drawToWindow()
{
	++_frameCount;
	Widget::drawToWindow();
}

LRESULT DemoWidget::processKeyDown(WPARAM wparam, LPARAM lparam)
{
	switch(wparam)
	{
	case VK_LEFT:
		preState();
		break;

	case VK_RIGHT:
		nextState();
		break;

	default:
		break;
	}

	_skiaView.processKeyDown(wparam, lparam);
	_gdiView.processKeyDown(wparam, lparam);
	_gdiplusView.processKeyDown(wparam, lparam);

	return Widget::processKeyDown(wparam, lparam);
}

void DemoWidget::initialize(int x, int y, int width, int height)
{
	Widget::init(x, y, width, height);
	_SkiaAnimatorView.hide();
	_GdiplusAnimatorView.hide();
	_skiaView.hide();
	_gdiView.hide();
	_gdiplusView.hide();

	KRect rect(0, 0, width, height);
	_SkiaAnimatorView.setRect(rect);
	_GdiplusAnimatorView.setRect(rect);
	_skiaView.setRect(rect);
	_gdiView.setRect(rect);
	_gdiplusView.setRect(rect);

	addView(&_SkiaAnimatorView);
	addView(&_GdiplusAnimatorView);
	addView(&_skiaView);
	addView(&_gdiView);
	addView(&_gdiplusView);
	startSkiaAnimate();
}

void DemoWidget::preState()
{
	switch(_curState)
	{
	case GDIPLUS_PRIMITIVE:
		clearCurState();
		startGdiPrimitive();
		break;

	case GDI_PRIMITIVE:
		clearCurState();
		startSkiaPrimitive();
		break;

	case SKIA_PRIMITIVE:
		clearCurState();
		startGdiplusAnimate();
		break;

	case GDIPLUS_ANIMATE:
		clearCurState();
		startSkiaAnimate();
		break;
	}
}

void DemoWidget::nextState()
{
	switch(_curState)
	{
	case SKIA_ANIMATE:
		clearCurState();
		startGdiplusAnimate();
		break;

	case GDIPLUS_ANIMATE:
		clearCurState();
		startSkiaPrimitive();
		break;

	case SKIA_PRIMITIVE:
		clearCurState();
		startGdiPrimitive();
		break;

	case GDI_PRIMITIVE:
		clearCurState();
		startGdiplusPrimitive();
		break;

	case GDIPLUS_PRIMITIVE:
		break;

	default:
		break;
	}
}

void DemoWidget::startSkiaAnimate()
{
	_curState = SKIA_ANIMATE;
	_SkiaAnimatorView.show();

	initCanvas(ak::SkiaGraphics);
	startAnimate();
	center();
	show();
}

void DemoWidget::startGdiplusAnimate()
{
	_curState = GDIPLUS_ANIMATE;
	_GdiplusAnimatorView.show();

	initCanvas(ak::GdiPlusGraphics);
	startAnimate();
	center();
	show();
}

void DemoWidget::startSkiaPrimitive()
{
	_curState = SKIA_PRIMITIVE;
	_skiaView.show();

	initCanvas(ak::SkiaGraphics);
	drawToWindow();
	center();
	show();
}

void DemoWidget::startGdiPrimitive()
{
	_curState = GDI_PRIMITIVE;
	_gdiView.show();

	initCanvas(ak::GdiGraphics);
	drawToWindow();
	center();
	show();
}

void DemoWidget::startGdiplusPrimitive()
{
	_curState = GDIPLUS_PRIMITIVE;
	_gdiplusView.show();

	initCanvas(ak::GdiPlusGraphics);
	drawToWindow();
	center();
	show();
}

void DemoWidget::endSkiaPrimitive()
{
	_skiaView.hide();
}

void DemoWidget::endGdiPrimitive()
{
	_gdiView.hide();
}

void DemoWidget::endGdiplusPrimitive()
{
	_gdiplusView.hide();
}

void DemoWidget::clearCurState()
{
	switch(_curState)
	{
	case SKIA_ANIMATE:
		endSkiaAnimate();
		break;

	case GDIPLUS_ANIMATE:
		endGdiplusAnimate();
		break;

	case SKIA_PRIMITIVE:
		endSkiaPrimitive();
		break;

	case GDIPLUS_PRIMITIVE:
		endGdiplusPrimitive();
		break;

	case GDI_PRIMITIVE:
		endGdiPrimitive();
		break;

	default:
		break;
	}
}

void DemoWidget::endSkiaAnimate()
{
	_SkiaAnimatorView.hide();
	stopAnimate();
}

void DemoWidget::endGdiplusAnimate()
{
	_GdiplusAnimatorView.hide();
	stopAnimate();
}