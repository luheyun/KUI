#include "UIDefine.h"
#include "GdiPlusGraphics.h"
#include <windows.h>
#include <gdiplus.h>
#include "GdiplusHelper.h"
#include "Size.h"
#include "KPen.h"
#include "KRect.h"
#include "KSolidBrush.h"
#include "GdiPlusImage.h"
#include "GdiplusRegion.h"

class GdiPlusGraphicsDelegate
{
public:
    GdiPlusGraphicsDelegate(int width, int height)
    {
		_bitmap = new Gdiplus::Bitmap(width, height, PixelFormat32bppARGB);
		_graphics = Gdiplus::Graphics::FromImage(_bitmap);
    }

    ~GdiPlusGraphicsDelegate()
    {
		if (nullptr != _bitmap)
		{
			delete _bitmap;
			_bitmap = nullptr;
		}

		if (nullptr != _graphics)
		{
			delete _graphics;
			_graphics = nullptr;
		}
    }

public:
    Gdiplus::Graphics* _graphics;
	Gdiplus::Bitmap* _bitmap;
	Gdiplus::BitmapData _bitmapData;
};

GdiPlusGraphics::GdiPlusGraphics(int width, int height)
    : Graphics(width, height)
{
    _gdiPlusGraphicsDelegate = new GdiPlusGraphicsDelegate(width, height);
}

GdiPlusGraphics::~GdiPlusGraphics()
{
	if (nullptr != _gdiPlusGraphicsDelegate)
	{
		delete _gdiPlusGraphicsDelegate;
		_gdiPlusGraphicsDelegate = nullptr;
	}
}

void* GdiPlusGraphics::lockBits()
{
	INVALID_POINTER_RETURN_NULL(_gdiPlusGraphicsDelegate);
	INVALID_POINTER_RETURN_NULL(_gdiPlusGraphicsDelegate->_bitmap);

	Gdiplus::Rect rect(0, 0, _gdiPlusGraphicsDelegate->_bitmap->GetWidth(), _gdiPlusGraphicsDelegate->_bitmap->GetHeight());
	_gdiPlusGraphicsDelegate->_bitmap->LockBits(&rect, Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &_gdiPlusGraphicsDelegate->_bitmapData);
	return _gdiPlusGraphicsDelegate->_bitmapData.Scan0;
}

void GdiPlusGraphics::unlockBits()
{
	INVALID_POINTER_RETURN(_gdiPlusGraphicsDelegate);
	INVALID_POINTER_RETURN(_gdiPlusGraphicsDelegate->_bitmap);

	_gdiPlusGraphicsDelegate->_bitmap->UnlockBits(&_gdiPlusGraphicsDelegate->_bitmapData);
}

void GdiPlusGraphics::clear(const Color& color)
{
	INVALID_POINTER_RETURN(_gdiPlusGraphicsDelegate);
	INVALID_POINTER_RETURN(_gdiPlusGraphicsDelegate->_graphics);
	Gdiplus::Color gdiplusColor = GdiplusHelper::colorToGdiplusColor(color);
	_gdiPlusGraphicsDelegate->_graphics->Clear(gdiplusColor);
}

bool GdiPlusGraphics::drawLine(KPen* pen, int x1, int y1, int x2, int y2)
{
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate);
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate->_graphics);
	INVALID_POINTER_RETURN_FALSE(pen);

	Gdiplus::Color gdiplusColor = GdiplusHelper::colorToGdiplusColor(pen->getColor());
	Gdiplus::Pen gdiplusPen(gdiplusColor, pen->getWidth());
	_gdiPlusGraphicsDelegate->_graphics->DrawLine(&gdiplusPen, x1, y1, x2 - 1, y2 - 1);
	return true;
}

bool GdiPlusGraphics::drawRect(KPen* pen, KRect& rect)
{
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate);
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate->_graphics);
	INVALID_POINTER_RETURN_FALSE(pen);

	Gdiplus::Color gpColor = GdiplusHelper::colorToGdiplusColor(pen->getColor());
	Gdiplus::Pen gpPen(gpColor, pen->getWidth());
	_gdiPlusGraphicsDelegate->_graphics->DrawRectangle(&gpPen, rect._left, rect._top, rect.width() - 1, rect.height() - 1);
	return true;
}

bool GdiPlusGraphics::fillRect(KBrush* brush, KRect& rect)
{
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate);
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate->_graphics);
	INVALID_POINTER_RETURN_FALSE(brush);

	switch(brush->getBrushType())
	{
	case ak::SolidBrush:
		{
			KSolidBrush* solidBrush = dynamic_cast<KSolidBrush*>(brush);
			INVALID_POINTER_RETURN_FALSE(solidBrush);
			Gdiplus::Color gpColor = GdiplusHelper::colorToGdiplusColor(solidBrush->getColor());
			Gdiplus::SolidBrush gpSolidBrush(gpColor);
			_gdiPlusGraphicsDelegate->_graphics->FillRectangle(&gpSolidBrush, rect._left, rect._top, rect.width() - 1, rect.height() - 1);
		}
	break;

	default:
		break;
	}

	return true;
}

bool GdiPlusGraphics::drawImage(Image* image, int x, int y, int nAlpha)
{
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate);
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate->_graphics);
	INVALID_POINTER_RETURN_FALSE(image);

	GdiplusImage* gdiplusImage = dynamic_cast<GdiplusImage*>(image);
	INVALID_POINTER_RETURN_FALSE(gdiplusImage);

	if (nAlpha == 255)
	{
		_gdiPlusGraphicsDelegate->_graphics->DrawImage(gdiplusImage->getGdiplusBitmap(), x, y);
	}
	else if (nAlpha >= 0 && nAlpha < 255)
	{
		Gdiplus::ImageAttributes imageAttr;
		Gdiplus::ColorMatrix colorMatrix = {1, 0, 0, 0, 0,
		                                    0, 1, 0, 0, 0,
		                                    0, 0, 1, 0, 0,
		                                    0, 0, 0, nAlpha / 255.0, 0,
		                                    0, 0, 0, 0, 1};
		imageAttr.SetColorMatrix(&colorMatrix);
		int width = gdiplusImage->getGdiplusBitmap()->GetWidth();
		int height = gdiplusImage->getGdiplusBitmap()->GetHeight();
		Gdiplus::Rect rect(x, y, width, height);
		_gdiPlusGraphicsDelegate->_graphics->DrawImage(gdiplusImage->getGdiplusBitmap(), rect, 0, 0, width, height, Gdiplus::UnitPixel, &imageAttr);
	}
	else
	{
		return false;
	}

	return true;
}

bool GdiPlusGraphics::drawImage(Image* image, int x, int y, float degrees)
{
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate);
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate->_graphics);
	INVALID_POINTER_RETURN_FALSE(image);

	GdiplusImage* gdiplusImage = dynamic_cast<GdiplusImage*>(image);
	INVALID_POINTER_RETURN_FALSE(gdiplusImage);

	Gdiplus::Bitmap* bitmap = gdiplusImage->getGdiplusBitmap();
	INVALID_POINTER_RETURN_FALSE(bitmap);

	int width = bitmap->GetWidth();
	int height = bitmap->GetHeight();

	Gdiplus::Rect rect(x, y, width, height);

	Gdiplus::Point points[] = {Gdiplus::Point(0, 0), Gdiplus::Point(width, 0), Gdiplus::Point(0, height)};
	Gdiplus::Matrix matrix(1, 0, 0, 1, x, y);
	matrix.Rotate(degrees);
	matrix.TransformPoints(points, 3);

	_gdiPlusGraphicsDelegate->_graphics->DrawImage(bitmap, points, 3);
	return true;
}

bool GdiPlusGraphics::drawString(const KString& str, int len, const KFont& font, const KPoint& pt, KBrush* brush)
{
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate);
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate->_graphics);

	int drawLen = len;

	if (-1 == drawLen)
	{
		drawLen = wcslen(str.c_str());
	}

	Gdiplus::Font* gdiplusFont = GdiplusHelper::fontToGdiplusFont(font);
	Gdiplus::PointF point = GdiplusHelper::pointToGdiplusPointF(pt);
	point.X -= 4;
	point.Y -= 16;
	Gdiplus::Brush* gdiplusBrush = GdiplusHelper::brushToGdiplusBrush(brush);
	Gdiplus::Status status = _gdiPlusGraphicsDelegate->_graphics->DrawString(str.c_str(), drawLen, gdiplusFont, point, gdiplusBrush);
	return true;
}

bool GdiPlusGraphics::setClip(const KRect& rect, ak::opMode mode)
{
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate);
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate->_graphics);

	Gdiplus::Rect gdiplusRect(rect._left, rect._top, rect.width(), rect.height());
	Gdiplus::CombineMode combineMode = GdiplusHelper::opModeToGdiplusCombineMode(mode);
	_gdiPlusGraphicsDelegate->_graphics->SetClip(gdiplusRect, combineMode);

	return true;
}

bool GdiPlusGraphics::resetClip()
{
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate);
	INVALID_POINTER_RETURN_FALSE(_gdiPlusGraphicsDelegate->_graphics);
	_gdiPlusGraphicsDelegate->_graphics->ResetClip();
	return true;
}