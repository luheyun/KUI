#pragma once
#include "gbitmaploader.h"

class GSkiaBitmapLoader : public GBitmapLoader
{
public:
    enum Format
    {
        Unknown_Format,
        BMP_Format,
        GIF_Format,
        ICO_Format,
        JPEG_Format,
        PNG_Format,
        WEBP_Format,
        TGA_Format
    };

public:
    GSkiaBitmapLoader();
    ~GSkiaBitmapLoader();

    GBitmapPtr loadBitmap(const GString & filename, const GString & format);
    GBitmapPtr loadBitmap(const GByte * pData, int len, const GString & format);
    virtual GBitmapPtr createBitmap(int width, int height, GImage::Format format);

private:
    Format getFileFormat(const GString & filename, const GString & format);
};