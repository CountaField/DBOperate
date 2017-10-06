#include "TableExtract.h"
//#include "Oracle_Connection.h"
#include <iostream>
#include <vector>

using namespace std;


vector<string> TableExtract::GetColumn(string table_name)
{
	printf("Getting Columns......\n");
	OracleConn::EnvCreate();
	vector<string> col_vec;
	for (auto id = table_name.begin(); id != table_name.end(); id++) {
		*id = toupper(*id);	
	}
	
	
	string sql_s = "SELECT COLUMN_NAME FROM USER_TAB_COLUMNS WHERE TABLE_NAME='" + table_name+"' order by column_id";

	char* sql = (char*)sql_s.data();
	StatmentInitial(sql);
	auto rs = OracleConn::rs;
	while (rs->next()) {
		col_vec.push_back(rs->getString(1));
	}
	//OracleConn::EndConn();
	return col_vec;
	
};


vector<string> TableExtract::GetTables() {
	OracleConn::EnvCreate();
	const string schem = "GSRDBA";
	vector<string> table_vec;
	StatmentInitial("SELECT TABLE_NAME FROM USER_TABLES");
	auto rs = OracleConn::rs;
	while (rs->next()) {
		table_vec.push_back(rs->getString(1));
	}
	OracleConn::EndConn();
	return table_vec;

};



