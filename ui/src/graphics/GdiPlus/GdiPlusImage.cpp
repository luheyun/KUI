#include "UIDefine.h"
#include "GdiPlusImage.h"
#include <windows.h>
#include <GdiPlus.h>
#include <string>

class GdiplusImageDelegate
{
public:
	GdiplusImageDelegate()
		: _bitmap(nullptr)
	{

	}

	GdiplusImageDelegate(int width, int height)
		: _bitmap(nullptr)
	{
		_bitmap = new Gdiplus::Bitmap(width, height, PixelFormat32bppARGB);
	}

	~GdiplusImageDelegate()
	{

	}

public:
	Gdiplus::Bitmap* _bitmap;
};

GdiplusImage::GdiplusImage()
{
	_gdiplusImageDelegate = new GdiplusImageDelegate;
}

GdiplusImage::GdiplusImage(int width, int height)
{
	_gdiplusImageDelegate = new GdiplusImageDelegate(width, height);
}

GdiplusImage::~GdiplusImage()
{
}

bool GdiplusImage::fromFile(char* file)
{
	INVALID_POINTER_RETURN_FALSE(_gdiplusImageDelegate);
	INVALID_POINTER_RETURN_FALSE(file);

 	int multiBytes = strlen(file);
 	int characters = MultiByteToWideChar(CP_ACP, 0, file, multiBytes, NULL, 0);
 	wchar_t* wFile = new wchar_t[characters + 1];
	memset(wFile, 0, (characters + 1) * sizeof(wchar_t));
 	MultiByteToWideChar(CP_ACP, 0, file, multiBytes, wFile, characters);

	if (nullptr != _gdiplusImageDelegate->_bitmap)
	{
		delete _gdiplusImageDelegate->_bitmap;
		_gdiplusImageDelegate->_bitmap = nullptr;
	}

	_gdiplusImageDelegate->_bitmap = Gdiplus::Bitmap::FromFile(wFile);
	return true;
}

Gdiplus::Bitmap* GdiplusImage::getGdiplusBitmap()
{
	INVALID_POINTER_RETURN_NULL(_gdiplusImageDelegate);
	return _gdiplusImageDelegate->_bitmap;
}