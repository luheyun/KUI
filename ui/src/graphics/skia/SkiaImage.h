#pragma once

#include "Image.h"

class SkBitmap;
class SkiaImageDelegate;

class SkiaImage : public Image
{
public:
    SkiaImage();
	SkiaImage(int width, int height);
    virtual ~SkiaImage();

    SkBitmap* getSkiaBitmap(); 
    // Image
   virtual bool fromFile(char* file) override;

private:
    SkiaImageDelegate* _skiaImageDelegate;
};