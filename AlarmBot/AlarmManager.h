#pragma once
#include "TelegramManager.h"
#include "TimeManager.h"
#include "Time_Def.h"
#include "schedule.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>



#define NOT_SCHEDULE_TIME -1



class AlarmManager
{
public:
	AlarmManager();
	~AlarmManager();

	bool initialize(std::string xml_path);
	void destroy();
	void update();

private:

public:
	TimeManager time;
	TelegramManager t_manager;
	
private:
	map<std::string, vector<ScheduleData*>> list;
};

