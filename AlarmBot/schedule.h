#pragma once

#include <string>
using namespace std;


class ScheduleData
{
public:
	ScheduleData( std::string time_in, std::string message_in)
	{
		time = time_in;
		message = message_in;
	};

	std::string get_time() { return time; }
	std::string get_message(){ return message; }
	std::string to_string() { return std::string("time : " + time + " / message : " + message); }

private:
	std::string time;
	std::string message;
};


