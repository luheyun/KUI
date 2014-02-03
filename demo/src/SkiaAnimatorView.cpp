#include "Stdafx.h"
#include "SkiaAnimatorView.h"
#include "Image.h"
#include "demo.h"
#include "KPoint.h"

const int IMAGE_WIDTH = 128;

SkiaAnimatorView::SkiaAnimatorView()
{
    init();
}

SkiaAnimatorView::~SkiaAnimatorView()
{

}

Image* SkiaAnimatorView::createImage()
{
	return Image::createImage(ak::SkiaGraphics);
}