// AlamBot.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "AlarmManager.h"
#include <iostream>
#include <direct.h>


#if _MSC_VER >= 1900
#	pragma comment(lib, "legacy_stdio_definitions.lib")
FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}
#endif



int main()
{
	AlarmManager* am = new AlarmManager();
	
	if (false == am->initialize("../data/schedule.xml"))
	{
		return 0;
	}
	
	do
	{
		am->update();
		Sleep( 1000 );
	}
	while( true );
	
	am->destroy();
	am = NULL;
    return 0;
}
