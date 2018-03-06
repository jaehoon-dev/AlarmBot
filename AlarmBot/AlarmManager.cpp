#include "stdafx.h"
#include "AlarmManager.h"
#include "schedule.h"
#include "custom_string.h"
#include "thirdparty/tinyxml2/tinyxml2.h"
#include <map>


AlarmManager::AlarmManager() {}

AlarmManager::~AlarmManager() 
{
	destroy();
}

void AlarmManager::destroy()
{
	curl_global_cleanup();
}

bool AlarmManager::initialize(std::string xml_path)
{
	t_manager.init();
	list.clear();

	tinyxml2::XMLError error_result;
	tinyxml2::XMLDocument xml_document;
	xml_document.WhitespaceMode();

	error_result = xml_document.LoadFile(xml_path.c_str());
	if (tinyxml2::XMLError::XML_SUCCESS != error_result)
	{
		std::cout << "Error - XML path" << std::endl;
		return false;
	}

	tinyxml2::XMLElement* xml_list = xml_document.FirstChildElement();
	if (nullptr == xml_list)
	{
		std::cout << "XML list에 data가 없당..." << std::endl;
		return false;
	}

	// XML Parse
	tinyxml2::XMLElement* list_element = xml_list->FirstChildElement();
	for (tinyxml2::XMLElement* child = list_element; child != nullptr; child = child->NextSiblingElement())
	{
		vector<ScheduleData*> vec;
		vec.clear();

		// map key
		std::string s_type = (std::string)child->Attribute("type");

		// schedule data		
		for (tinyxml2::XMLElement* sc = child->FirstChildElement(); sc != nullptr; sc = sc->NextSiblingElement())
		{
			std::string s_time = (std::string)sc->Attribute("time");
			std::string s_message = (std::string)sc->GetText();

			ScheduleData* data = new ScheduleData(s_time, s_message);

			vec.push_back(data);
		}

		list.insert(std::pair<std::string, vector<ScheduleData*>>(s_type, vec));
	}

	for (std::pair<std::string, vector<ScheduleData*>> d : list)
	{
		vector<ScheduleData*> vec_in = d.second;

		/*for (int i = 0; i < vec_in.size(); i++)
		{
			std::cout << "map data : " << vec_in[ i ]->to_string() << std::endl;
		}*/
	}

	return true;
}

void AlarmManager::update()
{
	//std::cout << time.get_HH_MM_SS_str() << std::endl;

	map<std::string, vector<ScheduleData*>>::iterator iter = list.find(time.get_day_of_week_str());
	vector<ScheduleData*> vec_in = iter->second;
	std::string now = "";

	std::string updates = t_manager.get_update();

	std::cout << updates << std::endl;

	int vec_size = vec_in.size();
	for (int i = 0; i < vec_size; i++)
	{
		now.clear();
		now.append(vec_in[ i ]->get_time());
		now.append(":05");

		if (time.get_HH_MM_SS_str() == now)
		{
			std::cout << "[ msg call ]" << time.get_HH_MM_SS_str() << std::endl;
			std::cout << vec_in[ i ]->get_message() << std::endl;

			t_manager.send_message
			(
				time.get_YYYY_MM_DD_str() +
				"\n" +
				vec_in[ i ]->get_message()
			);
		}
	}
}

