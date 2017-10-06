#pragma once
#include "timeconvert.h"
#include "DataExtract.h"

using namespace std;

class DataProcess {
public:

	DataProcess() = default;

	//DataProcess(string wellid) : wellid(wellid) {};


	//string wellid;


	double DataSum(string key_col,
		map<string, vector<string>> data_vec,
		vector<int> scope
	);

	double DataAvg(string key_col,
		map<string, vector<string>> data_vec,
		vector<int> scope
	);

	double DataProcess::DateCompare(string date_1, string date_2);
	
	void DataProcess::UpdateDataByCondition(
		/*
		1. key value £¨ps£º wellid£¬production_date)
		2. update column
		3. update value
		4. condition
		5. table name
		*/
		string key_value,
		string column,
		pair<string, string> value, //defined value type
		string condition,
		string table_name
	);

};