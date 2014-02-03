#pragma once

class StringHelper
{
public:
	StringHelper();
	~StringHelper();

	char* utf16ToUtf8(const wchar_t* utf16String);
	char* utf16ToAnsi(const wchar_t* utf16String);

private:
	void resizeCharBuf(int len);
	void resizeWCharBuf(int len);

private:
	int _charLen;
	char* _charBuf;

	int _wcharLen;
	wchar_t* _wcharBuf;
};