#include "stdafx.h"
#include "GdiplusView.h"
#include "Image.h"

GdiplusView::GdiplusView()
{

}

GdiplusView::~GdiplusView()
{

}

Image* GdiplusView::createBitmap(int width, int height)
{
	return Image::createImage(width, height, ak::GdiPlusGraphics);
}