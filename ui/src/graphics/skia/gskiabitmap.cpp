#include "StdAfx.h"
#include "gskiabitmap.h"

GSkiaBitmap::GSkiaBitmap(int width, int height, GImage::Format format)
{
    switch(format)
    {
    case GImage::ARGB32_Bitmap:
        bitmap.setConfig(SkBitmap::kARGB_8888_Config, width, height);
        bitmap.allocPixels();
        break;

    default:
        break;
    }

    _width = width;
    _height = height;
    _format = format;
    _pData = (unsigned char*)bitmap.getPixels();
}

GSkiaBitmap::~GSkiaBitmap(void)
{
}

void GSkiaBitmap::lock() const
{
    bitmap.lockPixels();
}

void GSkiaBitmap::unlock() const
{
    bitmap.unlockPixels();
}