#pragma once
#include <ctime>
#include <time.h>
#include <string>
using namespace std;


class TimeConvert {

public:
	
	TimeConvert()=default;
	TimeConvert(string s) : tstring(s) {};
	TimeConvert(time_t t) : stime(t) {};
	
	time_t StringToTime(string str);

	string TimeToString(time_t time);

	double DayDifference(time_t last_day, time_t first_day);

	
private:
	string tstring;
	time_t stime;


};