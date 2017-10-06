#pragma once
#include "Oracle_Connection.h"
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace oracle::occi;


class TableExtract:public  OracleConn {

public:
	//TableExtract() = default;6
	TableExtract() : OracleConn() {};
	TableExtract(string u, string p) : OracleConn(u, p) {};
	vector<string> GetTables();
	vector<string> GetColumn(string table_name);
	
	using OracleConn::userid;

private:
	string wellid;
	oracle::occi::Date shit;
	oracle::occi::Date prod_start_date;
	oracle::occi::Date production_date;
	int daily_prod_gas;
	int prod_cum_gas;

		
};


