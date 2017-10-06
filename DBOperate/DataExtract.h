#pragma once

#include "ComupteTools.h"
#include "TableExtract.h"
#include "Oracle_Connection.h"
#include <map>
//#include "Oracle_Connection.h"


using namespace std;

class DataExtract {



public:
	
	DataExtract() = default;

	
	void setTableName(string table_name);
	void setParameterVec(vector<string> par_vec);
	void setCondition(vector<string> cond_vec);
	TableExtract getTableInital();
	vector<string> getTableColumn();



private:

	TableExtract tb_extract;
	OracleConn gsrdb;
	string _table_name;
	vector<string> par_vec;
	string condition;
	
	map<string, vector<string>> full_table;
	
	map<string, map<string, vector<string>>> convert_table;
	
	void ExtractDataByTable(
		string table_name,
		vector<string> par_vec,
		string condition);
	

	void TidyUpDataByKeyCol(
		map <string, vector<string>> prod_data_map,
		string key_col);



protected:
	
	
	OracleConn getDBConnection();

	map<string, vector<string>> getFullTable(string table_name,
		vector<string> par_vec,
		string condition);

	map<string, map<string, vector<string>>> getConvertTableByKeyCol(map <string, vector<string>> prod_data_map,
		string key_col);

	


};

