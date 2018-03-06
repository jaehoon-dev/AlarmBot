#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager()
{
	reset();
}

TimeManager::~TimeManager()
{
	t_time = NULL;
}

void TimeManager::reset()
{
	t_time = time( NULL );
	_localtime( &t_time, &tm_struct );
}

int TimeManager::get_day_of_week()
{
	reset();
	return tm_struct.tm_wday;
}

std::string TimeManager::get_day_of_week_str()
{
	reset();
	
	int range = tm_struct.tm_wday;
	std::string temp;

	switch (range)
	{
		case 0: temp = "SUN"; break;
		case 1: temp = "MON"; break;
		case 2: temp = "TUE"; break;
		case 3: temp = "WED"; break;
		case 4: temp = "THU"; break;
		case 5: temp = "FRI"; break;
		case 6: temp = "SAT"; break;
	}

	return temp;
}

std::string TimeManager::get_HH_MM_str()
{
	reset();

	int h = tm_struct.tm_hour;
	int m = tm_struct.tm_min;

	std::string str = itostr(h) + ":" + itostr(m);
	return str;
}

std::string TimeManager::get_HH_MM_SS_str()
{
	reset();

	int h = tm_struct.tm_hour;
	int m = tm_struct.tm_min;
	int s = tm_struct.tm_sec;

	std::string str = itostr( h ) + ":" + itostr( m ) + ":" + itostr( s );
	return str;
}

std::string TimeManager::get_YYYY_MM_DD_str()
{
	reset();

	std::string str = itostr( tm_struct.tm_year + 1900 ) + "년 " + itostr( tm_struct.tm_mon + 1 ) + "월 " + itostr( tm_struct.tm_mday ) + "일";
	return str;
}

std::string TimeManager::itostr( int value )
{
	return ( value > 9 ) ? std::to_string( value ) : "0" + std::to_string( value );
}