#pragma once

#include "UIDefine.h"
#include "SkColor.h"
#include "Color.h"
#include "SkRect.h"
#include "KRect.h"
#include "KFont.h"
#include "SkTypeface.h"
#include "SkRegion.h"

namespace SkiaHelper
{
    SkColor colorToSkiaColor(Color color);
    SkRect rectToSkiaRect(const KRect& rect);
	SkTypeface::Style fontStyleToSkiaFontStyle(KFontStyle fontStyle);
	SkRegion::Op opModeToSkiaOp(ak::opMode opMode);
}