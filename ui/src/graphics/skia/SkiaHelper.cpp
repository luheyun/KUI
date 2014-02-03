#include "SkiaHelper.h"

namespace SkiaHelper
{
    SkColor colorToSkiaColor(Color color)
    {
        return color.getValue();
    }

    SkRect rectToSkiaRect(const KRect& rect)
    {
        SkRect skRect = {SkIntToScalar(rect._left), SkIntToScalar(rect._top), SkIntToScalar(rect._right), SkIntToScalar(rect._bottom)};
        return skRect;
    }

	SkTypeface::Style fontStyleToSkiaFontStyle(KFontStyle fontStyle)
	{
		SkTypeface::Style skFontStyle = SkTypeface::kNormal;

		switch(fontStyle)
		{
		case KFontStyleBold:
			skFontStyle = SkTypeface::kBold;
			break;

		case KFontStyleItalic:
			skFontStyle = SkTypeface::kItalic;
			break;

		case KFontStyleBoldItalic:
			skFontStyle = SkTypeface::kBoldItalic;
			break;

		default:
			break;
		}

		return skFontStyle;
	}

	SkRegion::Op opModeToSkiaOp(ak::opMode opMode)
	{
		SkRegion::Op skOp = SkRegion::kReplace_Op;

		switch(opMode)
		{
		case ak::kModeXor:
			skOp = SkRegion::kXOR_Op;
			break;

		case ak::kModeUnion:
			skOp = SkRegion::kUnion_Op;
			break;

		case ak::kModeReplace:
			skOp = SkRegion::kReplace_Op;
			break;

		case ak::kModeExclude:
			skOp = SkRegion::kReverseDifference_Op;
			break;

		case ak::kModeIntersect:
			skOp = SkRegion::kIntersect_Op;
			break;

		case ak::kModeComplement:
			skOp = SkRegion::kDifference_Op;
			break;

		default:
			break;
		}

		return skOp;
	}
}