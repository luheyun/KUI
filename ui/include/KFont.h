#pragma once

typedef enum
{
	kUnitWorld = 0,
	KUnitDisplay,
	KUnitPixel,
	KUnitPoint,
	KUnitInch,
	KUnitDocument,
	KUnitMillimeter,
} KFontUnit;

typedef enum
{
	KFontStyleRegular = 0,
	KFontStyleBold = 1,
	KFontStyleItalic = 2,
	KFontStyleBoldItalic = 3,
	kFontStyleUnderline = 4,
	kFontStyleStrikeout = 8,
} KFontStyle;

class KFontFamily;

class KFont
{
public:
	KFont(KFontFamily* fontFamily, int fontSize, KFontStyle fontStyle, KFontUnit fontUnit = KUnitPixel);
	~KFont();

	KFontFamily* getFontFamily() const;
	KFontStyle getFontStyle() const;
	KFontUnit getFontUnit() const;
	int getFontSize() const;

private:
	KFontFamily* _fontFamily;
	KFontStyle _fontStyle;
	KFontUnit _fontUnit;
	int _fontSize;

private:
	KFont() {}
};