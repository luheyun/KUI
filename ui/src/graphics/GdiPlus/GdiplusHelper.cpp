#include "GdiplusHelper.h"

#include "KFontFamily.h"
#include "KSolidBrush.h"

namespace GdiplusHelper
{
	Gdiplus::Color colorToGdiplusColor(Color color)
	{
		return Gdiplus::Color(color.getValue());
	}

	Gdiplus::Font* fontToGdiplusFont(const KFont& font)
	{
		Gdiplus::FontFamily fontFamily(font.getFontFamily()->getFamilyName().c_str());	
		return new Gdiplus::Font(&fontFamily, font.getFontSize(), font.getFontStyle(), (Gdiplus::Unit)font.getFontUnit());
	}

	Gdiplus::PointF pointToGdiplusPointF(const KPoint& point)
	{
		return Gdiplus::PointF(point._x, point._y);
	}

	Gdiplus::Brush* brushToGdiplusBrush(KBrush* brush)
	{
		Gdiplus::Brush* gdiplusBrush = nullptr;

		if (nullptr != brush)
		{
			if (ak::SolidBrush == brush->getBrushType())
			{
				KSolidBrush* solidBrush = dynamic_cast<KSolidBrush*>(brush);
				gdiplusBrush = new Gdiplus::SolidBrush(GdiplusHelper::colorToGdiplusColor(solidBrush->getColor()));
			}
		}

		return gdiplusBrush;
	}

	Gdiplus::CombineMode opModeToGdiplusCombineMode(ak::opMode mode)
	{
		Gdiplus::CombineMode opMode = Gdiplus::CombineModeReplace;

		switch(opMode)
		{
		case ak::kModeXor:
			opMode = Gdiplus::CombineModeXor;
			break;

		case ak::kModeUnion:
			opMode = Gdiplus::CombineModeUnion;
			break;

		case ak::kModeReplace:
			opMode = Gdiplus::CombineModeReplace;
			break;

		case ak::kModeExclude:
			opMode = Gdiplus::CombineModeExclude;
			break;

		case ak::kModeIntersect:
			opMode = Gdiplus::CombineModeIntersect;
			break;

		case ak::kModeComplement:
			opMode = Gdiplus::CombineModeComplement;
			break;

		default:
			break;
		}

		return opMode;
	}
}