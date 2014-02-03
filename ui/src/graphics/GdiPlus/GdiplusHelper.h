#pragma once

#include <windows.h>
#include <Gdiplus.h>
#include "UIDefine.h"
#include "Color.h"
#include "KFont.h"
#include "KPoint.h"
#include "Brush.h"

namespace GdiplusHelper
{
	Gdiplus::Color colorToGdiplusColor(Color color);
	Gdiplus::Font* fontToGdiplusFont(const KFont& font);
	Gdiplus::PointF pointToGdiplusPointF(const KPoint& point);
	Gdiplus::Brush* brushToGdiplusBrush(KBrush* brush);
	Gdiplus::CombineMode opModeToGdiplusCombineMode(ak::opMode mode);
}