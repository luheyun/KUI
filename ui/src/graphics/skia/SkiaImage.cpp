#include "UIDefine.h"
#include "SkiaImage.h"
#include "SkStream.h"
#include "SkBitmap.h"
#include "SkImageDecoder.h"

class SkiaImageDelegate
{
public:
    SkiaImageDelegate()
    {
//         _bitmap.setConfig(SkBitmap::kARGB_8888_Config, width, height);
//         _bitmap.allocPixels();
    }

	SkiaImageDelegate(int width, int height)
	{
		_bitmap.setConfig(SkBitmap::kARGB_8888_Config, width, height);
		_bitmap.allocPixels();
	}

    ~SkiaImageDelegate()
    {

    }

public:
     SkBitmap _bitmap;
};

SkiaImage::SkiaImage()
{
    _skiaImageDelegate = new SkiaImageDelegate;
}

SkiaImage::SkiaImage(int width, int height)
{
	_skiaImageDelegate = new SkiaImageDelegate(width, height);
}

SkiaImage::~SkiaImage()
{
}

SkBitmap* SkiaImage::getSkiaBitmap()
{
    INVALID_POINTER_RETURN_NULL(_skiaImageDelegate);
    return &(_skiaImageDelegate->_bitmap);
}

bool SkiaImage::fromFile(char* file)
{
    INVALID_POINTER_RETURN_FALSE(_skiaImageDelegate);
    SkFILEStream fileStream(file);
    SkImageDecoder* decoder = CreatePNGImageDecoder();

    if (decoder->decode(&fileStream, &_skiaImageDelegate->_bitmap, SkBitmap::kARGB_8888_Config, SkImageDecoder::kDecodePixels_Mode))
    {
        return true;
    }

    return false;
}