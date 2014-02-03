#include "stdafx.h"
#include "SkiaView.h"
#include "Image.h"

SkiaView::SkiaView()
{

}

SkiaView::~SkiaView()
{

}

Image* SkiaView::createBitmap(int width, int height)
{
	return Image::createImage(width, height, ak::SkiaGraphics);
}