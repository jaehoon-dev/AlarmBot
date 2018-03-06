#pragma once
#include <string>

namespace ALARM_TIME
{
	enum DayOfWeek
	{
		SUN = 0,
		MON,
		TUE,
		WED,
		THU,
		FRI,
		SAT,
	};
}


class AlarmSchedule
{
public:
	AlarmSchedule( int day_of_week, int h, int m, int s, std::string message )
	{
		_day_of_week = day_of_week;
		_h = h;
		_m = m;
		_s = s;
		_message = message;
	};

	inline int get_day_of_week() { return this->_day_of_week; };
	inline int get_h() { return this->_h; };
	inline int get_m() { return this->_m; };
	inline int get_s() { return this->_s; };
	inline std::string get_message() { return this->_message; };

private:
	int _day_of_week;
	int _h;
	int _m;
	int _s;
	std::string _message;
};

