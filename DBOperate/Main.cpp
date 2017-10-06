//#include "Oracle_Connection.h"
//#include "timeconvert.h"
//#include "TableExtract.h"
#include <typeinfo>
#include "Production_Base.h"
#include <map>
#include <utility>
#include "Well_Class.h"
#include <fstream>
#include <list>
#include "DataExtract.h"
//#include "hdfs.h"

//#include "ComupteTools.h"

//#include "ComupteTools.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <typeinfo>
#include "Well_Class.h"
using namespace std;

class test {
public:
	test() = default;
	ProductionBase prod;

private:
	string s1;
	
};

class test1 :public test {
public:
	
	test1() = default;
	
	
private:
	int i1 = 10;
};




void main() {
	
	test *test;
	test1 t1;
	test1 t2;
	t1.prod.setWellid("SN0002-01");
	t1.prod.setProdTableName("production_data");
	
	t1.prod.addArgs("PRODUCTION_DATE", ">","2017/01/01");

	t1.prod.addArgs("PRODUCTION_date", "<", "2017/01/02");
	//t1.prod.aParameterVec();
	//t1.prod.addArgs("casing_pressure", "<", "15");
	//t1.prod.addArgs("casing_pressure", ">", "0");
	
	//t1.prod.addParameterVec("PRoduction_date");

	printf("setp2...\n");
	
	
	
	t1.prod.ArgsClean();
	auto condition = t1.prod.getArgs();
	for (auto id = condition.begin(); id != condition.end(); id++) {
		cout << "this is args par........"<<id->first << endl;
	};
	cout << condition["CASING_PRESSURE"] << endl;

	//t1.prod.addParameterVec("wellid");
	//t1.prod.addParameterVec("daily_prod_gas");

	auto table = t1.prod.getReportTable();
	printf("setp3...\n");
	
	
	for (auto id = table.begin(); id != table.end(); id++) {
		for (auto id_v = id->second.begin(); id_v != id->second.end(); id_v++) {
			cout << id->first << " " << *id_v << endl;
		};
	};
	/*
	t2.prod.setWellid("SN0002-01");
	t2.prod.setProdTableName("RAW_DAILY_PRODUCTION");
	t2.prod.addParameterVec("wellid");
	t2.prod.addParameterVec("PRODUCTION_DATE");
	t2.prod.addParameterVec("daily_prod_gas");
	t2.prod.addArgs("DAILY_PROD_GAS", "is", "null");
	t2.prod.addArgs("production_date", ">", "2017/01/01");
	
	auto table = t2.prod.getReportTable();

	for (auto id = table.begin(); id != table.end(); id++) {
		for (auto id_v = id->second.begin(); id_v != id->second.end(); id_v++) {
			cout << id->first << " " << *id_v << endl;
		};
	};
	*/


	
	
	system("pause");
};
