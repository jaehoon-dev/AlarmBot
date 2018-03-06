#pragma once
#include <ctime>


inline static struct tm* _localtime( time_t* time, struct tm* _tm )
{
#ifdef _WIN32
	localtime_s( _tm, time );
#else
	localtime_r( time, _tm );
#endif
	return _tm;
}

class TimeManager
{
public:
	TimeManager();
	~TimeManager();



	std::string TimeManager::get_day_of_week_str();
	int TimeManager::get_day_of_week();
	std::string get_HH_MM_str();
	std::string get_HH_MM_SS_str();
	std::string get_YYYY_MM_DD_str();
	std::string itostr( int value );

private:
	void reset();
	
	struct tm	tm_struct;
	time_t		t_time;
};

