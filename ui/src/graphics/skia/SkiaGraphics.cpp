#include "UIDefine.h"
#include "SkiaGraphics.h"
#include "SkCanvas.h"
#include "SkDevice.h"
#include "SkiaHelper.h"
#include "SkRegion.h"
#include "Size.h"
#include "KPen.h"
#include "KFont.h"
#include "KPoint.h"
#include "KFontFamily.h"
#include "KSolidBrush.h"
#include "SkiaImage.h"
#include "SkiaRegion.h"

class SkiaGraphicsDelegate
{
public:
    SkiaGraphicsDelegate(int width, int height)
    {
        SkBitmap bitmap;
        bitmap.setConfig(SkBitmap::kARGB_8888_Config, width, height);
        bitmap.allocPixels();
        _canvas = new SkCanvas(bitmap);
    }

    ~SkiaGraphicsDelegate()
    {
		if (nullptr != _canvas)
		{
			delete _canvas;
			_canvas = nullptr;
		}
    }

public:
    SkCanvas* _canvas;
    SkPaint _paint;
};

SkiaGraphics::SkiaGraphics(int width, int height)
    : Graphics(width, height)
{
    _skiaGraphicsDelegate = new SkiaGraphicsDelegate(width, height);
}

SkiaGraphics::~SkiaGraphics()
{
    if (_skiaGraphicsDelegate)
    {
        delete _skiaGraphicsDelegate;
        _skiaGraphicsDelegate = NULL;
    }
}

void* SkiaGraphics::lockBits()
{
    INVALID_POINTER_RETURN_NULL(_skiaGraphicsDelegate);
    INVALID_POINTER_RETURN_NULL(_skiaGraphicsDelegate->_canvas);

    SkDevice* device = _skiaGraphicsDelegate->_canvas->getDevice();

    if (device)
    {
        const SkBitmap& bitmap = device->accessBitmap(false);
        return bitmap.getPixels();
    }

    return NULL;
}

void SkiaGraphics::clear(const Color& color)
{
	INVALID_POINTER_RETURN(_skiaGraphicsDelegate);
	INVALID_POINTER_RETURN(_skiaGraphicsDelegate->_canvas);
	SkColor skColor = SkiaHelper::colorToSkiaColor(color);
	_skiaGraphicsDelegate->_canvas->clear(skColor);
}

bool SkiaGraphics::drawLine(KPen* pen, int x1, int y1, int x2, int y2)
{
    INVALID_POINTER_RETURN_FALSE(pen);
    INVALID_POINTER_RETURN_FALSE(_skiaGraphicsDelegate);
    INVALID_POINTER_RETURN_FALSE(_skiaGraphicsDelegate->_canvas);

    SkColor color = SkiaHelper::colorToSkiaColor(pen->getColor());
    _skiaGraphicsDelegate->_paint.setColor(color);
    _skiaGraphicsDelegate->_canvas->drawLine(SkIntToScalar(x1), SkIntToScalar(y1), SkIntToScalar(x2), SkIntToScalar(y2), _skiaGraphicsDelegate->_paint);
    return true;
}

bool SkiaGraphics::drawImage(Image* image, int x, int y, int nAlpha)
{
    INVALID_POINTER_RETURN_FALSE(image);
    INVALID_POINTER_RETURN_FALSE(_skiaGraphicsDelegate);
    INVALID_POINTER_RETURN_FALSE(_skiaGraphicsDelegate->_canvas);

    SkiaImage* skiaImage = dynamic_cast<SkiaImage*>(image);
    INVALID_POINTER_RETURN_FALSE(skiaImage);
    SkBitmap* bitmap = skiaImage->getSkiaBitmap();
    INVALID_POINTER_RETURN_FALSE(bitmap);
    _skiaGraphicsDelegate->_paint.setAlpha(nAlpha);
    _skiaGraphicsDelegate->_canvas->drawBitmap(*bitmap, SkIntToScalar(x), SkIntToScalar(y), &_skiaGraphicsDelegate->_paint);
    return true;
}

bool SkiaGraphics::drawImage(Image* image, int x, int y, float degrees)
{
	INVALID_POINTER_RETURN_FALSE(image);
	INVALID_POINTER_RETURN_FALSE(_skiaGraphicsDelegate);
	INVALID_POINTER_RETURN_FALSE(_skiaGraphicsDelegate->_canvas);

	SkiaImage* skiaImage = dynamic_cast<SkiaImage*>(image);
	INVALID_POINTER_RETURN_FALSE(skiaImage);
	SkBitmap* bitmap = skiaImage->getSkiaBitmap();
	INVALID_POINTER_RETURN_FALSE(bitmap);
	SkMatrix skMatrix;
	skMatrix.setRotate(SkFloatToScalar(degrees), SkIntToScalar(x), SkIntToScalar(y));
	_skiaGraphicsDelegate->_canvas->drawBitmapMatrix(*bitmap, skMatrix, &_skiaGraphicsDelegate->_paint);
	return true;
}

bool SkiaGraphics::fillRect(KBrush* brush, KRect& rect)
{
    INVALID_POINTER_RETURN_FALSE(_skiaGraphicsDelegate);
    INVALID_POINTER_RETURN_FALSE(_skiaGraphicsDelegate->_canvas);
	INVALID_POINTER_RETURN_FALSE(brush);

	switch(brush->getBrushType())
    {
	case ak::SolidBrush:
		{
			KSolidBrush* solidBrush = dynamic_cast<KSolidBrush*>(brush);
			INVALID_POINTER_RETURN_FALSE(solidBrush);
			SkRect skRect = SkiaHelper::rectToSkiaRect(rect);
			_skiaGraphicsDelegate->_paint.setARGB(0x10, 0x00, 0x00, 0x00);
			SkColor skColor = SkiaHelper::colorToSkiaColor(solidBrush->getColor());
			_skiaGraphicsDelegate->_paint.setColor(skColor);
			_skiaGraphicsDelegate->_canvas->drawRect(skRect, _skiaGraphicsDelegate->_paint);
		}
	break;
	}
    return true;
}

bool SkiaGraphics::drawString(const KString& str, int len, const KFont& font, const KPoint& pt, KBrush* brush)
{
	INVALID_POINTER_RETURN_FALSE(_skiaGraphicsDelegate);
	INVALID_POINTER_RETURN_FALSE(_skiaGraphicsDelegate->_canvas);

	KFontFamily* fontFamily = font.getFontFamily();
	INVALID_POINTER_RETURN_FALSE(fontFamily);
	SkTypeface::Style style = SkiaHelper::fontStyleToSkiaFontStyle(font.getFontStyle());
	SkTypeface* typeFace = SkTypeface::CreateFromName(fontFamily->getFamilyName().getUtf8(), style);
	_skiaGraphicsDelegate->_paint.setTypeface(typeFace);
	_skiaGraphicsDelegate->_paint.setTextSize(SkIntToScalar(font.getFontSize()));
	_skiaGraphicsDelegate->_paint.setAntiAlias(true);
	_skiaGraphicsDelegate->_paint.setLCDRenderText(true);

	if (nullptr != brush)
	{
		if (ak::SolidBrush == brush->getBrushType())
		{
			KSolidBrush* solidBrush = dynamic_cast<KSolidBrush*>(brush);
			SkColor color = SkiaHelper::colorToSkiaColor(solidBrush->getColor());
			_skiaGraphicsDelegate->_paint.setColor(color);
		}
	}

	const char* utf8Str = str.getUtf8();
	int drawLen = len;

	if (-1 == drawLen)
	{
		drawLen = strlen(utf8Str);
	}

	_skiaGraphicsDelegate->_canvas->drawText((const void*)utf8Str, drawLen, SkIntToScalar(pt._x), SkIntToScalar(pt._y), _skiaGraphicsDelegate->_paint);
	return true;
}

bool SkiaGraphics::setClip(const KRect& rect, ak::opMode mode)
{
	INVALID_POINTER_RETURN_FALSE(_skiaGraphicsDelegate);
	INVALID_POINTER_RETURN_FALSE(_skiaGraphicsDelegate->_canvas);
	SkRect skRect = SkiaHelper::rectToSkiaRect(rect);
	SkRegion::Op skOp = SkiaHelper::opModeToSkiaOp(mode);
	_skiaGraphicsDelegate->_canvas->save(SkCanvas::kClip_SaveFlag);
	_skiaGraphicsDelegate->_canvas->clipRect(skRect, skOp);
	return true;
}

bool SkiaGraphics::resetClip()
{
	INVALID_POINTER_RETURN_FALSE(_skiaGraphicsDelegate);
	INVALID_POINTER_RETURN_FALSE(_skiaGraphicsDelegate->_canvas);
	_skiaGraphicsDelegate->_canvas->restoreToCount(1);
	return true;
}