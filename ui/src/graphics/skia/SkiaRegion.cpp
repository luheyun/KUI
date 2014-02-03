#include "UIDefine.h"
#include "SkiaRegion.h"
#include "SkRegion.h"

SkiaRegion::SkiaRegion()
	: _region(nullptr)
{
	_region = new SkRegion;
}

SkiaRegion::~SkiaRegion()
{
	if (nullptr != _region)
	{
		delete _region;
		_region = nullptr;
	}
}

SkRegion* SkiaRegion::getRegion()
{
	return _region;
}