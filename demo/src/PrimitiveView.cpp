#include "stdafx.h"
#include "PrimitiveView.h"
#include "Canvas.h"
#include "KPen.h"
#include "KSolidBrush.h"
#include "KFont.h"
#include "KFontFamily.h"
#include "KPoint.h"

const wchar_t* PRIMITIVE_NAME[] = {
	L"Line",
	L"Rect",
	L"Region",
	L"Bitmap",
    L"AlphaBitmap"
};

PrimitiveView::PrimitiveView()
	: _primitiveIndex(0)
	, _count(1)
	, _startTest(false)
	, _testTime(0)
{

}

PrimitiveView::~PrimitiveView()
{

}

void PrimitiveView::processKeyDown(WPARAM wparam, LPARAM lparam)
{
	if (!isShow())
	{
		return;
	}

	switch(wparam)
	{
	case 0x41: // a
		_primitiveIndex = _primitiveIndex > 0 ? _primitiveIndex - 1 : _primitiveIndex;
		schedulePaint();
		break;

	case 0x44: // d
		_primitiveIndex = _primitiveIndex < 4 ? _primitiveIndex + 1 : _primitiveIndex;
		schedulePaint();
		break;

	case 0x57: //w
		_count = _count < 1000000 ? _count * 10 : _count;
		schedulePaint();
		break;

	case 0x53: // s
		_count = _count > 1 ? _count / 10 : _count;
		schedulePaint();
		break;

	case VK_RETURN:
		_startTest = true;
		schedulePaint();
		break;

	default:
		break;
	}
}

bool PrimitiveView::doDraw(Canvas& canvas)
{
	if (_startTest)
	{
		test(canvas);
	}

	KFontFamily fontFamily(L"微软雅黑");
	KFont font(&fontFamily, 15, KFontStyleRegular, KUnitPixel);
	KSolidBrush fontBrush(Color(255, 100, 210, 110));

	KString description(L"a,d按键切换primitive, w,s按键修改数量, 回车键开始测试");
	KPoint pt(20, 70);
	canvas.drawString(description, -1, font, pt, &fontBrush);

	KString primitiveName(L"primitiveType  :  ");
	primitiveName += PRIMITIVE_NAME[_primitiveIndex];
	pt.set(20, 90);
	canvas.drawString(primitiveName, -1, font, pt, &fontBrush);

	KString primitiveCount(L"primitiveCount  :  ");
	primitiveCount += _count;
	pt.set(20, 110);
	canvas.drawString(primitiveCount, -1, font, pt, &fontBrush);

	KString result(L"Draw Time  :  ");
	result += _testTime;
	result += L"ms";

	pt.set(20, 130);
	canvas.drawString(result, -1, font, pt, &fontBrush);
	return true;
}

void PrimitiveView::test(Canvas& canvas)
{
	Image* image = createBitmap(500, 500);
	DWORD startTime = ::GetTickCount();

	if (0 == _primitiveIndex)
	{
		testLine(canvas);
	}
	else if (1 == _primitiveIndex)
	{
		testRect(canvas);
	}
	else if (2 == _primitiveIndex)
	{
		testClip(canvas);
	}
	else if (3 == _primitiveIndex)
	{
		testBitmap(canvas, image);
	}
    else
    {
        testAlphaBitmap(canvas, image);
    }

	_testTime = ::GetTickCount() - startTime;
	_startTest = false;
}

void PrimitiveView::testLine(Canvas& canvas)
{
	KPen pen(Color(255, 255, 0, 0));

	for (int i = 0; i < _count; ++i)
	{
		canvas.drawLine(&pen, 100, 200, 300, 200);
	}
}

void PrimitiveView::testRect(Canvas& canvas)
{
	KSolidBrush brush(Color(255, 255, 0, 0));
	KRect rect(100, 200, 300, 300);

	for (int i = 0; i < _count; ++i)
	{
		canvas.fillRect(&brush, rect);
	}
}

void PrimitiveView::testClip(Canvas& canvas)
{
	KRect rect(150, 250, 100, 100);
	canvas.setClip(rect, ak::kModeReplace);
	testRect(canvas);
	canvas.resetClip();
}

void PrimitiveView::testBitmap(Canvas& canvas, Image* bitmap)
{
	for (int i = 0; i < _count; ++i)
	{
		canvas.drawImage(bitmap, 100, 200);
	}
}

void PrimitiveView::testAlphaBitmap(Canvas& canvas, Image* bitmap)
{
    for (int i = 0; i < _count; ++i)
    {
        canvas.drawImage(bitmap, 100, 200, 200);
    }
}