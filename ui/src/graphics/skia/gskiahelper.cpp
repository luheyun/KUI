#include "StdAfx.h"
#include "gskiahelper.h"
#include "gfont.h"

namespace GSkiaHelper
{
    SkRect GRectToSkRect(const GRect & r)
    {
        SkRect rect = {(float)r.left, (float)r.top, (float)r.right, (float)r.bottom};
        return rect;
    }

    GRect SkRectToGRect(const SkRect & r)
    {
        return GRect((int)r.fLeft, (int)r.fTop, (int)r.fRight, (int)r.fBottom);
    }

    SkIRect GRectToSkIRect(const GRect & r)
    {
        SkIRect rect = {(int)r.left, (int)r.top, (int)r.right, (int)r.bottom};
        return rect;
    }

    SkColor GColorToSkColor(const GColor & c)
    {
        SkColor color;
        color = c.argb();
        return color;
    }

    SkTypeface::Style GFontStyleToSkStyle(const int & style)
    {
        SkTypeface::Style skStyle = SkTypeface::kNormal;

        if (GFont::Normal == style)
        {
           skStyle = SkTypeface::kNormal;
        }
        else if (GFont::Bold == style)
        {
            skStyle = SkTypeface::kBold;
        }
        else if (GFont::Italic == style)
        {
            skStyle = SkTypeface::kItalic;
        }

        return skStyle;
    }
}
