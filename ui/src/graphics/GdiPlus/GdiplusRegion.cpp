#include "UIDefine.h"
#include "GdiplusRegion.h"
#include <windows.h>
#include <GdiPlus.h>

GdiplusRegion::GdiplusRegion()
	: _region(nullptr)
{
	_region = new Gdiplus::Region;
}

GdiplusRegion::~GdiplusRegion()
{
	if (nullptr != _region)
	{
		delete _region;
		_region = nullptr;
	}
}

Gdiplus::Region* GdiplusRegion::getRegion()
{
	return _region;
}