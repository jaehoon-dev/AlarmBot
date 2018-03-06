// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



#define	IS_TEST	0


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "wldap32.lib" )

#ifdef _DEBUG
#	pragma comment(lib, "ssleay32MTd.lib")
#	pragma comment(lib, "libeay32MTd.lib")
#	pragma comment(lib, "libcurld.lib")
#else
#	pragma comment(lib, "ssleay32MT.lib")
#	pragma comment(lib, "libeay32MT.lib")
#	pragma comment(lib, "libcurl.lib")
#endif



#include <string>
#include <iostream>

using namespace std;
