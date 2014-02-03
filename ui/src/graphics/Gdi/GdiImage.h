#pragma once

#include "Image.h"

class GdiImageDelegate;

class GdiImage : public Image
{
public:
	GdiImage();
	GdiImage(int width, int height);
	virtual ~GdiImage();

    // Image
    virtual int width() override;
    virtual int height() override;

	void* getGdiBitmap();

private:
	GdiImageDelegate* _gdiImageDelegate;
};