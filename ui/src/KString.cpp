#include "UIDefine.h"
#include "KString.h"
#include "StringHelper.h"

const int MAX_NUMBER_LEN = 32;

KString::KString()
{
	_stringHelper = new StringHelper;
}

KString::KString(wchar_t* string)
	: _string(string)
{
	_stringHelper = new StringHelper;
}

KString::~KString()
{
	if (nullptr != _stringHelper)
	{
		delete _stringHelper;
		_stringHelper = nullptr;
	}
}

const KString& KString::operator += (const wchar_t* right)
{
	_string += right;
	return *this;
}

const KString& KString::operator += (const int& right)
{
	wchar_t strRight[MAX_NUMBER_LEN] = {0};
	swprintf_s(strRight, MAX_NUMBER_LEN, L"%d", right);
	_string += strRight;
	return *this;
}

const KString& KString::operator += (const unsigned long& right)
{
	wchar_t strRight[MAX_NUMBER_LEN] = {0};
	swprintf_s(strRight, MAX_NUMBER_LEN, L"%lu", right);
	_string += strRight;
	return *this;
}

void KString::clear()
{
	_string.clear();
}

bool KString::empty()
{
	return _string.empty();
}

const wchar_t* KString::c_str() const
{
	return _string.c_str();
}

const char* KString::getUtf8() const
{
	INVALID_POINTER_RETURN_NULL(_stringHelper);
	return _stringHelper->utf16ToUtf8(c_str());
}

const char* KString::getAnsi() const
{
	INVALID_POINTER_RETURN_NULL(_stringHelper);
	return _stringHelper->utf16ToAnsi(c_str());
}