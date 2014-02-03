#pragma once

#include "KRegion.h"

namespace Gdiplus
{
	class Region;
}

class GdiplusRegion : public KRegion
{
public:
	GdiplusRegion();
	virtual ~GdiplusRegion();

	Gdiplus::Region* getRegion();

private:
	Gdiplus::Region* _region;
};