#include "UIDefine.h"
#include "Image.h"
#include "SkiaImage.h"
#include "GdiPlusImage.h"
#include "GdiImage.h"

Image::Image()
{

}

Image::~Image()
{

}

Image* Image::createImage(int graphicsType)
{
	Image* image = nullptr;

	switch(graphicsType)
	{
	case ak::SkiaGraphics:
		{
			image = new SkiaImage;
		}
		break;

	case ak::GdiPlusGraphics:
		{
			image = new GdiplusImage;
		}
		break;

	case ak::GdiGraphics:
		{
			image = new GdiImage;
		}
		break;

	default:
		break;
	}

    return image;
}

Image* Image::createImage(int width, int height, int graphicsType)
{
	Image* image = nullptr;

	switch(graphicsType)
	{
	case ak::SkiaGraphics:
		{
			image = new SkiaImage(width, height);
		}
		break;

	case ak::GdiPlusGraphics:
		{
			image = new GdiplusImage(width, height);
		}
		break;

	case ak::GdiGraphics:
		{
			image = new GdiImage(width, height);
		}
		break;

	default:
		break;
	}

	return image;
}

bool Image::fromFile(char* file)
{
    return false;
}

int Image::width()
{
    return 0;
}

int Image::height()
{
    return 0;
}