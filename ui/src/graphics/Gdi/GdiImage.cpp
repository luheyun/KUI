#include "UIDefine.h"
#include "GdiImage.h"
#include <Windows.h>
#include <Wingdi.h>

class GdiImageDelegate
{
public:
	GdiImageDelegate()
		: _bitmap(nullptr)
		, _bits(nullptr)
        , _width(0)
        , _height(0)
	{

	}

	GdiImageDelegate(int width, int height)
		: _bitmap(nullptr)
		, _bits(nullptr)
        , _width(0)
        , _height(0)
	{
        _width = width;
        _height = height;
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
	}

	~GdiImageDelegate()
	{
		::DeleteObject(_bitmap);
		_bitmap = nullptr;
	}

public:
	HBITMAP _bitmap;
	void* _bits;
    int _width;
    int _height;
};

GdiImage::GdiImage()
{
	_gdiImageDelegate = new GdiImageDelegate;
}

GdiImage::GdiImage(int width, int height)
{
	_gdiImageDelegate = new GdiImageDelegate(width, height);
}

GdiImage::~GdiImage()
{

}

int GdiImage::width()
{
    INVALID_POINTER_RETURN_PARAM(_gdiImageDelegate, 0);
    return _gdiImageDelegate->_width;
}

int GdiImage::height()
{
    INVALID_POINTER_RETURN_PARAM(_gdiImageDelegate, 0);
    return _gdiImageDelegate->_height;
}

void* GdiImage::getGdiBitmap()
{
	INVALID_POINTER_RETURN_NULL(_gdiImageDelegate);
	return (void*)(_gdiImageDelegate->_bitmap);
}