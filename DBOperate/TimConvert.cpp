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
	tm_.tm_mon = month - 1;                    // �£�����tm�ṹ����·ݴ洢��ΧΪ0-11������tm_monΪint��ʱ������ȥ1��
	tm_.tm_mday = day;                         // �ա�
	tm_.tm_hour = hour;                        // ʱ��
	tm_.tm_min = minute;                       // �֡�
	tm_.tm_sec = second;                       // �롣
	tm_.tm_isdst = 0;                          // ������ʱ��
	time_t t_ = mktime(&tm_);                  // ��tm�ṹ��ת����time_t��ʽ��
	return t_;                                 // ����ֵ�� 
}

string TimeConvert::TimeToString(time_t time)
 {
	 tm *tm_ = localtime(&time);                // ��time_t��ʽת��Ϊtm�ṹ��
	 int year, month, day, hour, minute, second;// ����ʱ��ĸ���int��ʱ������
	 year = tm_->tm_year + 1900;                // ��ʱ�������꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬������ʱ����intΪtm_year����1900��
	 month = tm_->tm_mon + 1;                   // ��ʱ�������£�����tm�ṹ����·ݴ洢��ΧΪ0-11��������ʱ����intΪtm_mon����1��
	 day = tm_->tm_mday;                        // ��ʱ�������ա�
	 hour = tm_->tm_hour;                       // ��ʱ������ʱ��
	 minute = tm_->tm_min;                      // ��ʱ�������֡�
	 second = tm_->tm_sec;                      // ��ʱ�������롣
	 char yearStr[5], monthStr[3], dayStr[3], hourStr[3], minuteStr[3], secondStr[3];// ����ʱ��ĸ���char*������
	 sprintf(yearStr, "%d", year);              // �ꡣ
	 sprintf(monthStr, "%d", month);            // �¡�
	 sprintf(dayStr, "%d", day);                // �ա�
	 sprintf(hourStr, "%d", hour);              // ʱ�� 
	 sprintf(minuteStr, "%d", minute);          // �֡�
	 if (minuteStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
		   {
		         minuteStr[2] = '\0';
		         minuteStr[1] = minuteStr[0];
		         minuteStr[0] = '0';
		     }
	     sprintf(secondStr, "%d", second);          // �롣632633333333333445
	 if (secondStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
		     {
		         secondStr[2] = '\0';
		         secondStr[1] = secondStr[0];
		         secondStr[0] = '0';
		     }
	char s[20];                                // ����������ʱ��char*������
	sprintf(s, "%s/%s/%s %s:%s:%s", yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr);// ��������ʱ����ϲ���
	string str(s);                             // ����string����������������ʱ��char*������Ϊ���캯���Ĳ������롣
	return str;                                // ����ת������ʱ����string������
 }

double TimeConvert::DayDifference(time_t last_day, time_t first_day) {
	auto diffday= difftime(last_day, first_day);
	return diffday;
}

