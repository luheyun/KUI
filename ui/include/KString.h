#pragma once

class StringHelper;

class AK_API KString
{
public:
	KString();
	KString(wchar_t* string);
	~KString();

	const KString& operator += (const wchar_t* right);
	const KString& operator += (const int& right);
	const KString& operator += (const unsigned long& right);

	void clear();
	bool empty();
	const wchar_t* c_str() const;
	const char* getUtf8() const;
	const char* getAnsi() const;

private:
	StringHelper* _stringHelper;
	std::wstring _string;
};