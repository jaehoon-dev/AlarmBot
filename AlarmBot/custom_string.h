#pragma once

#include <string>

class CUSTOM_STRING
{
	enum
	{
		ERROR_NAME_OK,                                // OK
		ERROR_NAME_MAX_LENGTH,                // ���ڿ� ���� �ʰ�.
		ERROR_NAME_MIN_LENGTH,                // ���ڿ��� �ʹ� ª��.
		ERROR_NAME_SPECIAL_CODE,        // Ư���ڵ� ���.
		ERROR_NAME_VALUE,                        // ���� ���.
		ERROR_NAME_BLINK_MORE,                // ���� �ߺ� ���.
	};

public:
	static std::string trim( __in std::string& s, __in const std::string& drop = " " );
	static std::string rtrim( __in std::string s, __in const std::string& drop = " " );
	static std::string ltrim( __in std::string s, __in const std::string& drop = " " );
	static std::string trim_custom( __in std::string& s, __in const std::string& drop = " " );
	static std::string replace_all( __in const std::string &message, __in const std::string &pattern, __in const std::string &replace );

	static std::string urlencode( __in const std::string &source );
	static std::string urldecode( __in const std::string &source );
	static std::string urlencode2( __in const std::string &source );

	static std::string UTF8ToAnsi( __in std::string _in );
	static std::string AnsiToUTF8( __in std::string _in );

	static int Check_Filter_Name( const char* buffer, int minLen = 0, int maxLen = 0 );
};
