#pragma once
#ifndef _PRODUCTION_BASE
#define _PRODUCTION_BASE
#include "Well_Class.h"
//#include <map>
#include "Oracle_Connection.h"
#include "DataExtract.h"
#include "DataProcess.h"
#include "ComupteTools.h"

class ProductionBase:public DataExtract{

public:
	
	ProductionBase() = default;
	ProductionBase(string well_id) : wellid(well_id) {};
	void setWellid(string wellid);
	void setProdTableName(string table_name);
	void addParameterVec(string par);
	void addArgs(string col, string operation,string condition);
	void ArgsClean();
	vector<string> getParameterVec();
	string getTableName();
	vector<string> getColumns();
	map<string, string> getArgs();
	map<string, vector<string>> getReportTable();


	/*############################################<-  Official  ->############################################*/



	oracle::occi::Date prod_date;
	
	float prod_gas;
	float well_head_temp;
	float well_head_pressure;
	float casing_pressure;

	
	

   /*需要后期优化，函数返回值需要更改为模板*/
	double ProductionBase::ProcessProdData(
			map<string,vector<string>> well_prod_data,
			initializer_list<pair<string, string>> args);



	/*############################################<-  Official  ->############################################*/


private:

	string wellid;
	vector<string> well_vec;
	string _table_name;
	vector<string> par_vec = {};
	//initializer_list<pair<string, string>> args;
	map<string, string> args;
	/*string minDate();
	string maxDate();
	int	cumDays();
	int totalDays();
	int closeDays();
	vector<double> DailyProd();
	vector<string> ProdDate();*/
	map<string, vector<string>> _report_table;

	void ExtractDailyProdData(vector<string> wellid_vec,
		string table_name,
		vector<string> par_vec,
		map<string, string> args);
		//initializer_list<pair<string, string>> args); //Extract All Daily Prod Data From VW_PROD_ALL_SSOC
	
	
	void ExtractDailyProdData(); //Extract All Daily Prod Data From VW_PROD_ALL_SSOC


	map<string, string> ProductionBase::InstantToDailyDataProcess(
		string wellid,
		string key_col,
		map<string, map<string, vector<string>>> prod_table,
		initializer_list<pair<string, string>> args);
	
	int getTotalDays();

	void TidyUpArgs();

	string ComposeArgs();
};

#endif



















