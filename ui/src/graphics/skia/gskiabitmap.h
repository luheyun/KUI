#pragma once

#include "gbitmap.h"

#pragma warning(disable:4244)
#pragma warning(disable:4481)
#pragma warning(disable:4100)
#pragma warning(disable:4127)
#include "SkBitmap.h"
#pragma warning(default:4127)
#pragma warning(default:4100)
#pragma warning(default:4481)
#pragma warning(default:4244)

class GSkiaBitmap : public GBitmap
{
public:
    GSkiaBitmap(int width, int height, GImage::Format format = GImage::ARGB32_Bitmap);
    virtual ~GSkiaBitmap(void);

    virtual void lock() const;
    virtual void unlock() const;
private:
    SkBitmap bitmap;

    friend class GSkiaBitmapLoader;
    friend class GSkiaGraphic;
};

typedef boost::shared_ptr<GSkiaBitmap> GSkiaBitmapPtr;
typedef boost::weak_ptr<GSkiaBitmap> GSkiaBitmapWPtr;
