
#pragma once


#include <string>
#include "windows.h"
using namespace std;
static WCHAR strBuffer[512] = { '\0' };

static WCHAR* WCharTranslate(WCHAR* strMsg, ...)
{

	va_list args;
	va_start(args, strMsg);
	vswprintf_s(strBuffer, 512, strMsg, args);
	strBuffer[511] = L'\0';
	va_end(args);

	return (strBuffer);
}

static RECT GetStringRect(ID3DXFont* font, ID3DXSprite* sprite, WCHAR* string)
{
	RECT r;
	if (FAILED(font->DrawText(
		sprite,
		string,
		wcslen(string),
		&r,
		DT_CALCRECT,
		0
		)))
	{

	};
	return r;
}

static long GetStringWidth(ID3DXFont* font, ID3DXSprite* sprite, WCHAR* string)
{
	RECT r = GetStringRect(font, sprite, string);
	return r.right - r.left;
}
class TString
{
private:
	WCHAR wcString[512];
	WCHAR strBuffer[512];
	char cBuffer[512];
	int textSize = 8;

public:
	TString(const WCHAR* string)
	{
		wsprintf(wcString, L"%s", string);
		wsprintf(strBuffer, L"%s", L"\0");
		sprintf_s(cBuffer, "%s", "\0");
		ListIndex = 0;
		Next = NULL;
	}
	TString(WCHAR* string)
	{
		wsprintf(wcString, L"%s", string);
		wsprintf(strBuffer, L"%s", L"\0");
		sprintf_s(cBuffer, "%s", "\0");
		ListIndex = 0;
		Next = NULL;
	}
	TString(float value)
	{

		wsprintf(wcString, L"%s", WCharTranslate(L"%0.2f", value));
		wsprintf(strBuffer, L"%s", L"\0");
		sprintf_s(cBuffer, "%s", "\0");
		ListIndex = 0;
		Next = NULL;
	}
	TString(int value)
	{

		wsprintf(wcString, L"%d", value);
		wsprintf(strBuffer, L"%s", L"\0");
		sprintf_s(cBuffer, "%s", "\0");
		ListIndex = 0;
		Next = NULL;
	}
	TString(char* string)
	{

		WCHAR buffer[512];
		size_t convertedChars = 0;
		size_t newsize = strlen(string) + 1;
		mbstowcs_s(&convertedChars, buffer, newsize, string, _TRUNCATE);
		wsprintf(wcString, L"%s", buffer);
		wsprintf(strBuffer, L"%s", L"\0");
		sprintf_s(cBuffer, "%s", "\0");
		ListIndex = 0;
		Next = NULL;
	}
	TString()
	{
		wsprintf(wcString, L"%s", L"\0");
		wsprintf(strBuffer, L"%s", L"\0");
		sprintf_s(cBuffer, "%s", "\0");
		ListIndex = 0;
		Next = NULL;

	};
	~TString(){};
	TString(string str)
	{
		*this = str;
	}

	WCHAR* operator = (string str)
	{
		*this = str.c_str();
		return wcString;
	}
	int ListIndex = -1;
	TString* Next = NULL;
	int Length(){ return  wcslen(wcString); }
	WCHAR* w_char() { return wcString; }
	char*  c_str()
	{

		int ret;
		size_t len = wcslen(wcString) + 1;
		ret = wcstombs_s(&len, cBuffer, wcString, sizeof(cBuffer));
		if (ret == 512) cBuffer[511] = '\0';
		return cBuffer;
	}

	WCHAR* operator += (int iValue)
	{
		WCHAR buffer[512];
		wsprintf(buffer, L"%d", iValue);
		wsprintf(wcString, L"%s%s", wcString, buffer);

		return wcString;
	}
	WCHAR* operator =  (int iValue)
	{
		wsprintf(wcString, L"%d", iValue);
		return wcString;
	}
	TString operator + (TString& string)
	{
		*this += string;
		return *this;

	}
	WCHAR* operator + (WCHAR* string)
	{
		*this += string;
		return wcString;

	}
	WCHAR* operator += (float iValue)
	{
		wsprintf(wcString, L"%s%s", wcString, WCharTranslate(L"%0.4f", iValue));
		return wcString;
	}
	WCHAR* operator =  (float iValue)
	{
		wsprintf(wcString, L"%s", WCharTranslate(L"%0.4f", iValue));
		return wcString;
	}

	WCHAR* operator += (WCHAR* string)
	{
		WCHAR buffer[512];
		wsprintf(buffer, L"%s", string);
		wsprintf(wcString, L"%s%s", wcString, buffer);

		return wcString;
	}
	WCHAR* operator += (TString string)
	{
		WCHAR buffer[512];
		wsprintf(buffer, L"%s", string.w_char());
		wsprintf(wcString, L"%s%s", wcString, buffer);
		return wcString;
	}
	WCHAR* operator = (WCHAR* string)
	{
		//WCHAR buffer[512];
		wsprintf(wcString, L"%s", string);
		//wsprintf(wcString, L"%s%s", wcString, buffer);

		return wcString;
	}
	int  operator = (LONG value)
	{
		textSize = (int)value;
		return textSize;
	}
	WCHAR* operator = (char* string)
	{

		size_t convertedChars = 0;
		size_t newsize = strlen(string) + 1;
		mbstowcs_s(&convertedChars, wcString, newsize, string, _TRUNCATE);
		return wcString;
	}
	WCHAR* operator += (char* string)
	{
		WCHAR buffer[512];
		size_t convertedChars = 0;
		size_t newsize = strlen(string) + 1;
		mbstowcs_s(&convertedChars, buffer, newsize, string, _TRUNCATE);
		wsprintf(wcString, L"%s%s", wcString, buffer);
		return wcString;
	}

	bool operator == (TString string)
	{
		if (strcmp(this->c_str(), string.c_str()) == 0)
		{
			return true;
		}
		return false;
	}

};


