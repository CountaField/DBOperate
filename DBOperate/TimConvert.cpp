#include "timeconvert.h"
#include <typeinfo>
#include <string>
#include <ctime>
#include <iostream>
#include <time.h>

using namespace std;




time_t TimeConvert::StringToTime(string str) {

	char *cha = (char*)str.data();
	tm tm_;
	int year, month, day, hour, minute, second;
	sscanf_s(cha, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	tm_.tm_year = year - 1900;
	tm_.tm_mon = month - 1;                    // 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
	tm_.tm_mday = day;                         // 日。
	tm_.tm_hour = hour;                        // 时。
	tm_.tm_min = minute;                       // 分。
	tm_.tm_sec = second;                       // 秒。
	tm_.tm_isdst = 0;                          // 非夏令时。
	time_t t_ = mktime(&tm_);                  // 将tm结构体转换成time_t格式。
	return t_;                                 // 返回值。 
}

string TimeConvert::TimeToString(time_t time)
 {
	 tm *tm_ = localtime(&time);                // 将time_t格式转换为tm结构体
	 int year, month, day, hour, minute, second;// 定义时间的各个int临时变量。
	 year = tm_->tm_year + 1900;                // 临时变量，年，由于tm结构体存储的是从1900年开始的时间，所以临时变量int为tm_year加上1900。
	 month = tm_->tm_mon + 1;                   // 临时变量，月，由于tm结构体的月份存储范围为0-11，所以临时变量int为tm_mon加上1。
	 day = tm_->tm_mday;                        // 临时变量，日。
	 hour = tm_->tm_hour;                       // 临时变量，时。
	 minute = tm_->tm_min;                      // 临时变量，分。
	 second = tm_->tm_sec;                      // 临时变量，秒。
	 char yearStr[5], monthStr[3], dayStr[3], hourStr[3], minuteStr[3], secondStr[3];// 定义时间的各个char*变量。
	 sprintf(yearStr, "%d", year);              // 年。
	 sprintf(monthStr, "%d", month);            // 月。
	 sprintf(dayStr, "%d", day);                // 日。
	 sprintf(hourStr, "%d", hour);              // 时。 
	 sprintf(minuteStr, "%d", minute);          // 分。
	 if (minuteStr[1] == '\0')                  // 如果分为一位，如5，则需要转换字符串为两位，如05。
		   {
		         minuteStr[2] = '\0';
		         minuteStr[1] = minuteStr[0];
		         minuteStr[0] = '0';
		     }
	     sprintf(secondStr, "%d", second);          // 秒。632633333333333445
	 if (secondStr[1] == '\0')                  // 如果秒为一位，如5，则需要转换字符串为两位，如05。
		     {
		         secondStr[2] = '\0';
		         secondStr[1] = secondStr[0];
		         secondStr[0] = '0';
		     }
	char s[20];                                // 定义总日期时间char*变量。
	sprintf(s, "%s/%s/%s %s:%s:%s", yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr);// 将年月日时分秒合并。
	string str(s);                             // 定义string变量，并将总日期时间char*变量作为构造函数的参数传入。
	return str;                                // 返回转换日期时间后的string变量。
 }

double TimeConvert::DayDifference(time_t last_day, time_t first_day) {
	auto diffday= difftime(last_day, first_day);
	return diffday;
}

