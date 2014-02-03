#include "UIDefine.h"
#include "KFont.h"
#include "KFontFamily.h"

KFont::KFont(KFontFamily* fontFamily, int fontSize, KFontStyle fontStyle, KFontUnit fontUnit)
	: _fontFamily(fontFamily)
	, _fontSize(fontSize)
	, _fontStyle(fontStyle)
	, _fontUnit(fontUnit)
{

}

KFont::~KFont()
{

}

KFontFamily* KFont::getFontFamily() const
{
	return _fontFamily;
}

KFontStyle KFont::getFontStyle() const
{
	return _fontStyle;
}

KFontUnit KFont::getFontUnit() const
{
	return _fontUnit;
}

int KFont::getFontSize() const
{
	return _fontSize;
}