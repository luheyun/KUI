#include "grect.h"
#include "gcolor.h"

#pragma warning(disable:4244)
#pragma warning(disable:4481)
#pragma warning(disable:4100)
#pragma warning(disable:4127)
#include "SkRect.h"
#include "SkColor.h"
#include "SkTypeface.h"
#pragma warning(default:4127)
#pragma warning(default:4100)
#pragma warning(default:4481)
#pragma warning(default:4244)

namespace GSkiaHelper
{
    SkRect GRectToSkRect(const GRect & r);
    GRect SkRectToGRect(const SkRect & r);
    SkIRect GRectToSkIRect(const GRect & r);
    SkColor GColorToSkColor(const GColor & c);
    SkTypeface::Style GFontStyleToSkStyle(const int & style);
}