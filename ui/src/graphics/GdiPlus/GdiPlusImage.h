#pragma once

#include "Image.h"

class GdiplusImageDelegate;

namespace Gdiplus
{
	class Bitmap;
}

class GdiplusImage : public Image
{
public:
	GdiplusImage();
	GdiplusImage(int width, int height);
	virtual ~GdiplusImage();

	// Image
	virtual bool fromFile(char* file) override;

	// GdiplusImage
	Gdiplus::Bitmap* getGdiplusBitmap();

private:
	GdiplusImageDelegate* _gdiplusImageDelegate;
};