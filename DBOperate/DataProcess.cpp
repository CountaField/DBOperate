#include "DataProcess.h"



double DataProcess::DataSum(string key_col, map<string, vector<string>> data_vec, vector<int> scope) {
	auto id = scope.begin();
	double sum_result = 0.0;
		//stringToNum<double>(data_vec[key_col][*id].c_str());
	printf("sum is %f\n", sum_result);
	
	double iter_num = 0.0;
	while (id!=scope.end()){		
		string &s2n = data_vec[key_col][*id];
			iter_num = stringToNum<double>(s2n.c_str());
		sum_result += iter_num;
		id++;
	}
		return sum_result;

}



double DataProcess::DataAvg(string key_col, map<string, vector<string>> data_vec, vector<int> scope) {
		
	double sum = DataSum(key_col, data_vec, scope);
	double avg = 0.0;
	
	avg = sum / scope.size();
	printf("sum %f, scope szie %.2lf\n", sum, scope.size());
	return avg;
}

double DataProcess::DateCompare(string date_str_1,string date_str_2) {
	TimeConvert ST;
	time_t date1=ST.StringToTime(date_str_1);
	time_t date2 = ST.StringToTime(date_str_2);
	
	auto diff=ST.DayDifference(date1, date2);

	return diff;

}

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
	string table_name) {
	OracleConn gsrdb;
	string update_value;
	
	if (value.first == "STRING") {
		update_value = "'" + value.second + "'";
	}
	else {
		update_value =  value.second ;
	}


	string update_sql = "update " + table_name + " set " + column +
		"=" + update_value + " where " + condition + " ";

	for (auto id = update_sql.begin(); id != update_sql.end(); id++) {
		*id = toupper(*id);
	};

	char* sql = (char*)update_sql.data();
	printf("%s\n", update_sql.c_str());
	gsrdb.Update(sql);
	gsrdb.EndConn();
};


