#include "stdafx.h"
#include "DemoView.h"
#include "KFontFamily.h"
#include "KFont.h"
#include "Canvas.h"
#include "KSolidBrush.h"
#include "KPoint.h"
#include "demo.h"

DemoView::DemoView()
	: _startTime(0)
{

}

DemoView::~DemoView()
{

}

bool DemoView::draw(Canvas& canvas)
{
	_startTime = ::GetTickCount();
	canvas.clear(Color(0, 0, 0, 0));
	KSolidBrush solidBrush(Color(200, 0, 0, 0));
	canvas.fillRect(&solidBrush, KRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	doDraw(canvas);
	showGraphicsType(canvas);
	return true;
}

void DemoView::showGraphicsType(Canvas& canvas)
{
	KFontFamily fontFamily(L"Î¢ÈíÑÅºÚ");
	KFont font(&fontFamily, 15, KFontStyleRegular, KUnitPixel);
	KSolidBrush fontBrush(Color(255, 100, 210, 110));

	KString graphicsStr(L"Draw With ");

	if (ak::SkiaGraphics == canvas.getGraphicsType())
	{
		graphicsStr += L"Skia";
	}
	else if (ak::GdiPlusGraphics == canvas.getGraphicsType())
	{
		graphicsStr += L"Gdiplus";
	}
	else
	{
		graphicsStr += L"Gdi";
	}

	KPoint pt(20, 50);
	canvas.drawString(graphicsStr, -1, font, pt, &fontBrush);
}