#include "stdafx.h"
#include "GdiView.h"
#include "KSolidBrush.h"
#include "KPen.h"
#include "Canvas.h"
#include "Size.h"
#include "Image.h"

GdiView::GdiView()
{

}

GdiView::~GdiView()
{

}

bool GdiView::draw(Canvas& canvas)
{
	DemoView::draw(canvas);
	char* bits = (char*)canvas.lockBits();
	Size size = canvas.getCanvasSize();
	char* bit = nullptr;

	for (int j = 0; j < size._height; ++j)
	{
		for (int i = 0; i < size._width; ++i)
		{
			bit = &bits[(j * size._width + i) * 4];
			bit[3] = 0xff;
// 			bit[0] = 0x00;
// 			bit[1] = 0x00;
// 			bit[2] = 0x00;
		}
	}

	return true;
}

Image* GdiView::createBitmap(int width, int height)
{
    return Image::createImage(width, height, ak::GdiGraphics);
}