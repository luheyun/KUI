#include "StringHelper.h"
#include <windows.h>

const int DEFAULT_BUFFER_LEN = 1024;

StringHelper::StringHelper()
	: _charLen(0)
	, _charBuf(nullptr)
	, _wcharLen(0)
	, _wcharBuf(nullptr)
{
	_charLen = DEFAULT_BUFFER_LEN;
	_charBuf = (char*)malloc(DEFAULT_BUFFER_LEN * sizeof(char));
	_wcharLen = DEFAULT_BUFFER_LEN;
	_wcharBuf = (wchar_t*)malloc(DEFAULT_BUFFER_LEN * sizeof(wchar_t));
}

StringHelper::~StringHelper()
{
	free(_charBuf);
	free(_wcharBuf);
}

char* StringHelper::utf16ToUtf8(const wchar_t* utf16String)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, utf16String, -1, nullptr, 0, nullptr, nullptr);
	resizeCharBuf(len + 1);
	WideCharToMultiByte(CP_UTF8, 0, utf16String, -1, _charBuf, len, nullptr, nullptr);
	return _charBuf;
}

char* StringHelper::utf16ToAnsi(const wchar_t* utf16String)
{
	int len = WideCharToMultiByte(CP_ACP, 0, utf16String, -1, nullptr, 0, nullptr, nullptr);
	resizeCharBuf(len + 1);
	WideCharToMultiByte(CP_ACP, 0, utf16String, -1, _charBuf, len, nullptr, nullptr);
	return _charBuf;
}

void StringHelper::resizeCharBuf(int len)
{
	if (len > _charLen)
	{
		_charLen = len;
		_charBuf = (char*)realloc(_charBuf, len * sizeof(char));
	}

	memset(_charBuf, 0, _charLen * sizeof(char));
}

void StringHelper::resizeWCharBuf(int len)
{
	if (len > _wcharLen)
	{
		_wcharLen = len;
		_wcharBuf = (wchar_t*)realloc(_wcharBuf, len * sizeof(wchar_t));
	}

	memset(_wcharBuf, 0, _wcharLen * sizeof(wchar_t));
}