#pragma once

#include <string>

class CUSTOM_STRING
{
	enum
	{
		ERROR_NAME_OK,                                // OK
		ERROR_NAME_MAX_LENGTH,                // 문자열 길이 초과.
		ERROR_NAME_MIN_LENGTH,                // 문자열이 너무 짧음.
		ERROR_NAME_SPECIAL_CODE,        // 특수코드 사용.
		ERROR_NAME_VALUE,                        // 숫자 사용.
		ERROR_NAME_BLINK_MORE,                // 공백 중복 사용.
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
