#pragma once

class KString;

class KFontFamily
{
public:
	KFontFamily(wchar_t* fontFamily);
	~KFontFamily();

	const KString& getFamilyName() const;

private:
	KString _familyName;

private:
	KFontFamily() {}
};