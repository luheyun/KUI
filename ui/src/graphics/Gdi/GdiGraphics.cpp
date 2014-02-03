#include "UIDefine.h"
#include "GdiGraphics.h"
#include "Size.h"
#include "KRect.h"
#include "KSolidBrush.h"
#include "KPen.h"
#include "KFont.h"
#include "KFontFamily.h"
#include "KPoint.h"
#include "GdiHelper.h"
#include "GdiImage.h"
#include <Windows.h>
#include <Wingdi.h>

class GdiGraphicsDelegate
{
public:
	GdiGraphicsDelegate(int width, int height)
		: _bits(nullptr)
		, _width(width)
		, _height(height)
	{
		HDC hdc = ::GetDC(nullptr);
		_hMemDc = ::CreateCompatibleDC(hdc);

		BITMAPINFOHEADER bmpInfoHeader = { 0 };  
		bmpInfoHeader.biSize = sizeof( BITMAPINFOHEADER);  
		bmpInfoHeader.biWidth = width;  
		bmpInfoHeader.biHeight = -height;  
		bmpInfoHeader.biPlanes = 1;
		bmpInfoHeader.biBitCount = 32;  
		bmpInfoHeader.biCompression = BI_RGB;  
		bmpInfoHeader.biClrUsed = 0;  
		bmpInfoHeader.biSizeImage = 0;
		bmpInfoHeader.biClrImportant = 0;

		_bitmap = ::CreateDIBSection(NULL, (PBITMAPINFO )&bmpInfoHeader, DIB_RGB_COLORS , (void**)&_bits, nullptr, 0);
		_oldBitmap = (HBITMAP)::SelectObject(_hMemDc, _bitmap);
	}

	~GdiGraphicsDelegate()
	{
		if (nullptr != _hMemDc)
		{
			::SelectObject(_hMemDc, _oldBitmap);
			::DeleteDC(_hMemDc);
			_hMemDc = nullptr;
		}

		if (nullptr != _bitmap)
		{
			::DeleteObject(_bitmap);
			_bitmap = nullptr;
		}

		_bits = nullptr;
	}

public:
	int _width;
	int _height;
	void* _bits;
	HBITMAP _bitmap;
	HBITMAP _oldBitmap;
	HDC _hMemDc;
};

GdiGraphics::GdiGraphics(int width, int height)
	: Graphics(width, height)
{
	_gdiGraphicsDelegate = new GdiGraphicsDelegate(width, height);
}

GdiGraphics::~GdiGraphics()
{
	if (nullptr != _gdiGraphicsDelegate)
	{
		delete _gdiGraphicsDelegate;
		_gdiGraphicsDelegate = nullptr;
	}
}

void* GdiGraphics::lockBits()
{
	INVALID_POINTER_RETURN_NULL(_gdiGraphicsDelegate);
	return _gdiGraphicsDelegate->_bits;
}

void GdiGraphics::clear(const Color& color)
{
	INVALID_POINTER_RETURN(_gdiGraphicsDelegate);
	INVALID_POINTER_RETURN(_gdiGraphicsDelegate->_bits);
	memset(_gdiGraphicsDelegate->_bits, 0xff, _gdiGraphicsDelegate->_width * _gdiGraphicsDelegate->_height * 4);
}

bool GdiGraphics::drawLine(KPen* pen, int x1, int y1, int x2, int y2)
{
	INVALID_POINTER_RETURN_FALSE(_gdiGraphicsDelegate);
	INVALID_POINTER_RETURN_FALSE(pen);

	HDC hMemDc = _gdiGraphicsDelegate->_hMemDc;
	Color color = pen->getColor();
	COLORREF gdiColor = RGB(color.getR(), color.getG(), color.getB());
	HPEN gdiPen = ::CreatePen(PS_SOLID, pen->getWidth(), gdiColor);
	HPEN oldPen = (HPEN)::SelectObject(hMemDc, gdiPen);
	::MoveToEx(hMemDc, x1, y1, nullptr);
	::LineTo(hMemDc, x2, y2);
	::SelectObject(hMemDc, oldPen);
	::DeleteObject(gdiPen);
	return true;
}

bool GdiGraphics::drawImage(Image* image, int x, int y, int nAlpha)
{
    INVALID_POINTER_RETURN_FALSE(_gdiGraphicsDelegate);

    GdiImage* gdiImage = dynamic_cast<GdiImage*>(image);
    INVALID_POINTER_RETURN_FALSE(gdiImage);

    HBITMAP bitmap = (HBITMAP)gdiImage->getGdiBitmap();
    INVALID_POINTER_RETURN_FALSE(bitmap);

    HDC hMemDc = _gdiGraphicsDelegate->_hMemDc;
    HDC hSrcDc = ::CreateCompatibleDC(hMemDc);
    HBITMAP oldBitmap = (HBITMAP)::SelectObject(hSrcDc, bitmap);
//     HBRUSH brush = ::CreateSolidBrush(RGB(255, 0, 0));
//     ::SelectObject(hSrcDc, brush);
//     ::Rectangle(hSrcDc, 0, 0, image->width(), image->height());

    if (nAlpha >= 0 && nAlpha < 255)
    {
        BLENDFUNCTION blendFunc = {AC_SRC_OVER, 0, nAlpha, AC_SRC_ALPHA};
        ::AlphaBlend(hMemDc, x, y, image->width(), image->height(), hSrcDc, 0, 0, image->width(), image->height(), blendFunc);
    }
    else
    {
        ::BitBlt(hMemDc, x, y, image->width(), image->height(), hSrcDc, 0, 0, SRCCOPY);
    }

    ::SelectObject(hSrcDc, oldBitmap);
    ::DeleteDC(hSrcDc);
    return true;
}

bool GdiGraphics::drawRect(KPen* pen, KRect& rect)
{
	INVALID_POINTER_RETURN_FALSE(_gdiGraphicsDelegate);
	INVALID_POINTER_RETURN_FALSE(pen);

	HDC hMemDc = _gdiGraphicsDelegate->_hMemDc;
	Color color = pen->getColor();
	COLORREF gdiColor = RGB(color.getR(), color.getG(), color.getB());
	HPEN gdiPen = ::CreatePen(PS_SOLID, pen->getWidth(), gdiColor);
	HPEN oldPen = (HPEN)::SelectObject(hMemDc, gdiPen);
	::Rectangle(hMemDc, rect._left, rect._top, rect._right, rect._bottom);
	::SelectObject(hMemDc, oldPen);
	::DeleteObject(gdiPen);
	return true;
}

bool GdiGraphics::fillRect(KBrush* brush, KRect& rect)
{
	INVALID_POINTER_RETURN_FALSE(_gdiGraphicsDelegate);
	INVALID_POINTER_RETURN_FALSE(brush);

	HDC hMemDc = _gdiGraphicsDelegate->_hMemDc;

	switch(brush->getBrushType())
	{
	case ak::SolidBrush:
		{
			KSolidBrush* solidBrush = dynamic_cast<KSolidBrush*>(brush);
			INVALID_POINTER_RETURN_FALSE(solidBrush);
			Color color = solidBrush->getColor();
			COLORREF gdiColor = RGB(color.getR(), color.getG(), color.getB());
			HBRUSH gdiBrush = CreateSolidBrush(gdiColor);
			HBRUSH gdiOldBrush = (HBRUSH)::SelectObject(hMemDc, gdiBrush);
			::Rectangle(hMemDc, rect._left, rect._top, rect._right, rect._bottom);
			::SelectObject(hMemDc, gdiOldBrush);
			::DeleteObject(gdiBrush);
		}
		break;
	}

	return true;
}

bool GdiGraphics::drawString(const KString& str, int len, const KFont& font, const KPoint& pt, KBrush* brush)
{
	INVALID_POINTER_RETURN_FALSE(_gdiGraphicsDelegate);

	HDC hMemDc = _gdiGraphicsDelegate->_hMemDc;

	LOGFONT logFont;
	memset(&logFont, 0, sizeof(logFont));
	logFont.lfCharSet   = DEFAULT_CHARSET;
	logFont.lfHeight    = -MulDiv(font.getFontSize(), GetDeviceCaps(hMemDc, LOGPIXELSY), 72);

	if (KFontStyleRegular & font.getFontStyle())
	{
		logFont.lfWeight = FW_NORMAL;
	}
	else if (KFontStyleBold & font.getFontStyle())
	{
		logFont.lfWeight = FW_BOLD;
	}
	else
	{
		logFont.lfWeight = FW_DONTCARE;
	}

	if (kFontStyleUnderline & font.getFontStyle())
	{
		logFont.lfUnderline = true;
	}

	if (kFontStyleStrikeout & font.getFontStyle())
	{
		logFont.lfStrikeOut = true;
	}

	if (KFontStyleItalic & font.getFontStyle())
	{
		logFont.lfItalic = true;
	}

	KFontFamily* fontFamily = font.getFontFamily(); 
	wcscpy_s(logFont.lfFaceName, LF_FACESIZE, fontFamily->getFamilyName().c_str());
	HFONT gdiFont = ::CreateFontIndirect(&logFont);

	// ¼ÆËã´óÐ¡
	RECT rect = {0};
	::DrawTextEx(hMemDc, (LPWSTR)str.c_str(), -1, &rect, DT_CALCRECT | DT_CENTER, nullptr);
	rect.left = pt._x;
	rect.top = pt._y;
	rect.right += pt._x;
	rect.bottom += pt._y;
	
	if (ak::SolidBrush == brush->getBrushType())
	{
		KSolidBrush* solidBrush = dynamic_cast<KSolidBrush*>(brush);
		Color color = solidBrush->getColor();
		COLORREF textColor = RGB(color.getR(), color.getG(), color.getB());
		COLORREF oldColor = ::SetTextColor(hMemDc, textColor);
	}

	int oldMode = ::SetBkMode(hMemDc, TRANSPARENT);
	::DrawTextEx(hMemDc, (LPWSTR)str.c_str(), -1, &rect, DT_CENTER, nullptr);
	::SetBkMode(hMemDc, oldMode);
	return true;
}

bool GdiGraphics::setClip(const KRect& rect, ak::opMode mode)
{
	INVALID_POINTER_RETURN_FALSE(_gdiGraphicsDelegate);

	HDC hMemDc = _gdiGraphicsDelegate->_hMemDc;
	HRGN hRgn = ::CreateRectRgn(rect._left, rect._top, rect._right, rect._bottom);
	int opMode = GdiHelper::opModeToGdiOp(mode);

	HRGN hDestRgn = nullptr;

	if (1 == ::GetClipRgn(hMemDc, hDestRgn))
	{
		::CombineRgn(hDestRgn, hDestRgn, hRgn, mode);
		::SelectClipRgn(hMemDc, hDestRgn);
		::DeleteObject(hDestRgn);
	}
	else
	{
		::SelectClipRgn(hMemDc, hRgn);
	}

	::DeleteObject(hRgn);

	return true;
}

bool GdiGraphics::resetClip()
{
	INVALID_POINTER_RETURN_FALSE(_gdiGraphicsDelegate);
	HDC hMemDc = _gdiGraphicsDelegate->_hMemDc;
	::SelectClipRgn(hMemDc, nullptr);
	return true;
}