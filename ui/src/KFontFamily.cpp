#include "UIDefine.h"
#include "KFontFamily.h"

KFontFamily::KFontFamily(wchar_t* fontFamily)
	: _familyName(fontFamily)
{

}

KFontFamily::~KFontFamily()
{

}

const KString& KFontFamily::getFamilyName() const
{
	return _familyName;
}