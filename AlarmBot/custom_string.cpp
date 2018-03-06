#include "stdafx.h"
#include "custom_string.h"
#include "libcurl/include/curl.h"

const char HEX2DEC[256] =
{
	/*       0  1  2  3   4  5  6  7   8  9  A  B   C  D  E  F */
	/* 0 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* 1 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* 2 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* 3 */  0, 1, 2, 3,  4, 5, 6, 7,  8, 9,-1,-1, -1,-1,-1,-1,

	/* 4 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* 5 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* 6 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* 7 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,

	/* 8 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* 9 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* A */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* B */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,

	/* C */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* D */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* E */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
	/* F */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1
};

const char SAFE[256] =
{
	/*      0 1 2 3  4 5 6 7  8 9 A B  C D E F */
	/* 0 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 1 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 2 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 3 */ 1,1,1,1, 1,1,1,1, 1,1,0,0, 0,0,0,0,

	/* 4 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
	/* 5 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,
	/* 6 */ 0,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
	/* 7 */ 1,1,1,1, 1,1,1,1, 1,1,1,0, 0,0,0,0,

	/* 8 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* 9 */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* A */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* B */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,

	/* C */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* D */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* E */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	/* F */ 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
};

std::string CUSTOM_STRING::trim( __in std::string& s, __in const std::string& drop /*= " " */ )
{
	std::string r = s.erase( s.find_last_not_of( drop ) + 1 );
	return r.erase( 0, r.find_first_not_of( drop ) );
}

std::string CUSTOM_STRING::rtrim( __in std::string s, __in const std::string& drop /*= " " */ )
{
	std::string r = s.erase( s.find_last_not_of( drop ) + 1 );
	return r;
}

std::string CUSTOM_STRING::ltrim( __in std::string s, __in const std::string& drop /*= " " */ )
{
	std::string r = s.erase( 0, s.find_first_not_of( drop ) );
	return r;
}

std::string CUSTOM_STRING::trim_custom( __in std::string& s, __in const std::string& drop /*= " " */ )
{
	std::string r = s.erase( 0, s.find_first_not_of( " " ) );
	r = r.erase( 0, r.find_first_not_of( "\n" ) );
	r = r.erase( r.find_last_not_of( drop ) + 1 );
	r = r.erase( r.find_last_not_of( "\n" ) + 1 );
	r = CUSTOM_STRING::replace_all( r, "\n \n", "\n" );
	r = CUSTOM_STRING::replace_all( r, "\n\n", "\n" );
	return r.erase( 0, r.find_first_not_of( drop ) );
}

std::string CUSTOM_STRING::replace_all( __in const std::string &message, __in const std::string &pattern, __in const std::string &replace )
{
	std::string result = message;
	std::string::size_type pos = 0;
	std::string::size_type offset = 0;

	while ( (pos = result.find( pattern, offset )) != std::string::npos )
	{
		result.replace( result.begin() + pos, result.begin() + pos + pattern.size(), replace );
		offset = pos + replace.size();
	}

	return result;
}

std::string CUSTOM_STRING::urlencode( __in const std::string &source )
{
	std::string result_string;

	char hex[4];
	for ( const char &c : source )
	{
		if ( (c > 47 && c < 57) ||
			 (c > 64 && c < 92) ||
			 (c > 96 && c < 123) ||
			 c == '-' || c == '.' || c == '_' )
			result_string += c ;
		else
		{
			sprintf_s( hex, "%%%02X", (unsigned char)c );
			result_string.append( hex );
		}
	}

	return result_string;
}

std::string CUSTOM_STRING::urldecode( __in const std::string &source )
{
	// Note from RFC1630: "Sequences which start with a percent
	// sign but are not followed by two hexadecimal characters
	// (0-9, A-F) are reserved for future extension"

	const unsigned char * pSrc = (const unsigned char *)source.c_str();
	const int SRC_LEN = source.length();
	const unsigned char * const SRC_END = pSrc + SRC_LEN;
	// last decodable '%' 
	const unsigned char * const SRC_LAST_DEC = SRC_END - 2;

	char * const pStart = new char[SRC_LEN];
	char * pEnd = pStart;

	while ( pSrc < SRC_LAST_DEC )
	{
		if ( *pSrc == '%' )
		{
			char dec1, dec2;
			if ( -1 != (dec1 = HEX2DEC[*(pSrc + 1)])
				 && -1 != (dec2 = HEX2DEC[*(pSrc + 2)]) )
			{
				*pEnd++ = (dec1 << 4) + dec2;
				pSrc += 3;
				continue;
			}
		}

		*pEnd++ = *pSrc++;
	}

	// the last 2- chars
	while ( pSrc < SRC_END )
		*pEnd++ = *pSrc++;

	std::string sResult( pStart, pEnd );
	delete[] pStart;
	return sResult;
}

// std::string UriEncode( const std::string & sSrc )
// {
// 	const char DEC2HEX[16 + 1] = "0123456789ABCDEF";
// 	const unsigned char * pSrc = (const unsigned char *)sSrc.c_str();
// 	const int SRC_LEN = sSrc.length();
// 	unsigned char * const pStart = new unsigned char[SRC_LEN * 3];
// 	unsigned char * pEnd = pStart;
// 	const unsigned char * const SRC_END = pSrc + SRC_LEN;
// 
// 	for ( ; pSrc < SRC_END; ++pSrc )
// 	{
// 		if ( SAFE[*pSrc] )
// 			*pEnd++ = *pSrc;
// 		else
// 		{
// 			// escape this char
// 			*pEnd++ = '%';
// 			*pEnd++ = DEC2HEX[*pSrc >> 4];
// 			*pEnd++ = DEC2HEX[*pSrc & 0x0F];
// 		}
// 	}
// 
// 	std::string sResult( (char *)pStart, (char *)pEnd );
// 	delete[] pStart;
// 	return sResult;
// }

std::string CUSTOM_STRING::urlencode2( __in const std::string &source )
{
	std::string result_string;

	char hex[6];
	for ( const char &c : source )
	{
		if ( (c > 47 && c < 57) ||
			(c > 64 && c < 92) ||
			 (c > 96 && c < 123) ||
			 c == '-' || c == '.' || c == '_' )
			result_string += c;
		else
		{
			sprintf_s( hex, "%%25%02X", c );
			result_string.append( hex );
		}
	}

	return result_string;
}


std::string CUSTOM_STRING::UTF8ToAnsi( __in std::string _in )
{
	std::string result;
	int nLength = MultiByteToWideChar( CP_UTF8, 0, _in.c_str(), _in.length() + 1, NULL, NULL );
	BSTR bstrWide = SysAllocStringLen( NULL, nLength );
	MultiByteToWideChar( CP_UTF8, 0, _in.c_str(), _in.length() + 1, bstrWide, nLength );
	nLength = WideCharToMultiByte( CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL );

	char *pszAnsi = new char[nLength];
	ZeroMemory( pszAnsi, nLength );
	WideCharToMultiByte( CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL );
	SysFreeString( bstrWide );
	result = pszAnsi;
	delete[] pszAnsi;

	return result;
}

std::string CUSTOM_STRING::AnsiToUTF8( __in std::string _in )
{
	std::string result;
	int     nLength, nLength2;
	BSTR    bstrCode;
	char*   pszUTFCode = NULL;

	nLength = MultiByteToWideChar( CP_ACP, 0, _in.c_str(), lstrlenA( _in.c_str() ), NULL, NULL );
	bstrCode = SysAllocStringLen( NULL, nLength );
	MultiByteToWideChar( CP_ACP, 0, _in.c_str(), lstrlenA( _in.c_str() ), bstrCode, nLength );

	nLength2 = WideCharToMultiByte( CP_UTF8, 0, bstrCode, -1, pszUTFCode, 0, NULL, NULL );

	pszUTFCode = new char[nLength2];
	memset( pszUTFCode, 0, nLength2 );
	WideCharToMultiByte( CP_UTF8, 0, bstrCode, -1, pszUTFCode, nLength2, NULL, NULL );

	result = pszUTFCode;
	delete[] pszUTFCode;

	return result;
}


int CUSTOM_STRING::Check_Filter_Name( const char* buffer, int minLen, int maxLen )
{
	int len = strlen( buffer );

	if ( minLen != 0 || maxLen != 0 )
	{
		// 길이 검사
		// if( len > NAME_LEN )
		if ( len >= maxLen )
			return ERROR_NAME_MAX_LENGTH;
		else if ( len < minLen )
			return ERROR_NAME_MIN_LENGTH;
	}

	// 특수문자 검사
	for ( int x = 0; x < len; ++x )
	{
		if ( ((unsigned char)buffer[x] >= 0xB0) &&
			((unsigned char)buffer[x] <= 0xC8) &&
			 ((unsigned char)buffer[x + 1] >= 0xA1) &&
			 ((unsigned char)buffer[x + 1] <= 0xFE) )
		{
			// 한글 해당 부분
			x++;
			continue;
		}
		else if ( ((unsigned char)buffer[x] >= 0xCA) &&
			((unsigned char)buffer[x] <= 0xFD) &&
				  ((unsigned char)buffer[x + 1] >= 0xA1) &&
				  ((unsigned char)buffer[x + 1] <= 0xFE) )
		{
			// 한자 해당 부분
			return ERROR_NAME_SPECIAL_CODE;
		}
		else if ( (((unsigned char)buffer[x] >= 0x41) &&
			((unsigned char)buffer[x] <= 0x5A)) ||
				  (((unsigned char)buffer[x] >= 0x61) &&
				  ((unsigned char)buffer[x] <= 0x7A)) )
		{
			// 영어 해당 부분
			continue;
		}
		else if ( (buffer[x] >= '0') && (buffer[x] <= '9') )
		{
			// 숫자 처리 부분
			continue;
		}
		else if ( ((unsigned char)buffer[x] >= 0xA1) &&
			((unsigned char)buffer[x + 1] >= 0xA1) )
		{
			// 2byte special char
			return ERROR_NAME_SPECIAL_CODE;
		}
		else
		{
			// 1byte special character 
			return ERROR_NAME_SPECIAL_CODE;
		}
	}

	return ERROR_NAME_OK;
}