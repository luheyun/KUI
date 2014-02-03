#include "stdafx.h"
#include "gskiabitmaploader.h"
#include "gbitmapmanger.h"
#include "gskiabitmap.h"

#pragma warning(disable:4244)
#pragma warning(disable:4481)
#pragma warning(disable:4100)
#pragma warning(disable:4127)
#include "SkImageDecoder.h"
#include "SkStream.h"
#pragma warning(default:4127)
#pragma warning(default:4100)
#pragma warning(default:4481)
#pragma warning(default:4244)

GSkiaBitmapLoader::GSkiaBitmapLoader()
{

}

GSkiaBitmapLoader::~GSkiaBitmapLoader()
{

}

GBitmapPtr GSkiaBitmapLoader::loadBitmap(const GString & filename, const GString & format)
{
    SkFILEStream stream(filename.toAnsi());

    if (stream.isValid())
    {
        Format fileFormat = getFileFormat(filename, format);
        SkImageDecoder* decoder = NULL;

        switch(fileFormat)
        {
        case PNG_Format:
            decoder = CreatePNGImageDecoder();
            break;

        case BMP_Format:
            break;

        case ICO_Format:
            break;

        case GIF_Format:
            break;

        case JPEG_Format:
            break;

        case WEBP_Format:
            break;

        case TGA_Format:
            break;

        default:
            G_ASSERT(false);
            return GBitmapPtr();
        }

        GSkiaBitmapPtr pBitmap(new GSkiaBitmap(0, 0));

        if (decoder)
        {
            stream.rewind();

            if (decoder->decode(&stream, &(pBitmap->bitmap), SkBitmap::kARGB_8888_Config, SkImageDecoder::kDecodePixels_Mode))
            {
                pBitmap->_width = pBitmap->bitmap.width();
                pBitmap->_height = pBitmap->bitmap.height();
                pBitmap->_pData = (unsigned char*)pBitmap->bitmap.getPixels();
                pBitmap->_format = GImage::ARGB32_Bitmap;
                return pBitmap;
            }
        }
    }

    return GBitmapPtr();
}

GBitmapPtr GSkiaBitmapLoader::loadBitmap(const GByte * pData, int len, const GString & format)
{
    G_ASSERT(pData);
    G_UNUSED(len);
    G_UNUSED(format);
    return GBitmapPtr();
}

GSkiaBitmapLoader::Format GSkiaBitmapLoader::getFileFormat(const GString & filename, const GString & format)
{
    G_UNUSED2(filename,format);
    return PNG_Format;
}

GBitmapPtr GSkiaBitmapLoader::createBitmap(int width, int height, GImage::Format format)
{
    return GSkiaBitmapPtr(new GSkiaBitmap(width, height, format));
}

GBitmapLoaderInsertTemplate<GSkiaBitmapLoader> tt;