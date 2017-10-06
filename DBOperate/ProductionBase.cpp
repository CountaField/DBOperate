
#include "Production_Base.h"
#include "TableExtract.h"
#include "timeconvert.h"
#include <cstdio>



map<string, vector<string>> ProductionBase::getReportTable() {
	map<string, vector<string>> report_table;
	if (this->wellid.empty()) {
		printf("ERROR Please initial Wellid\n");
		return report_table;
	}


	if (this->_table_name.empty()) {

		printf("ERROR Please initial Table Name\n");
		return report_table;
	}

	if (this->_report_table.empty()) {
		if (par_vec.empty()) {

			par_vec = this->getTableInital().GetColumn(this->_table_name);
		}
		//printf("start to extract data");
		ExtractDailyProdData(well_vec, _table_name, par_vec, args);
		return this->_report_table;
	}
	return this->_report_table;
	
}


void ProductionBase::ExtractDailyProdData() {

	string table_name = "VW_PROD_ALL_SSOC";
	string where_wellid_sub = " wellid in ('" + this->wellid + "')";
	string final_condition = " where "+where_wellid_sub;
	vector<string> par_vec = {};
	map<string, vector<string>> full_table = this->getFullTable(table_name, par_vec, final_condition);
	this->_report_table = full_table;

}


void ProductionBase::ExtractDailyProdData(vector<string> wellid_vec,
	string table_name,
	vector<string> par_vec,
	map<string, string> args)
	//initializer_list<pair<string, string>> args)


 {
	
	string date_condition;
	string compare_condition;
	string order_condition;
	string where_wellid_sub;
	string well_list_str;
	string min_date, max_date;
	string final_condition="WHERE ";
	//printf("start to extract data2.....");
	/*##########################   1.初始化 table_name   #######################*/
	if (table_name.empty()) {

		table_name = "VW_PROD_ALL_SSOC";

	}

	/*##########################   2. 根据 wellid_vec 列表初始化 well_list_string 字符串  #######################*/
	if (!wellid_vec.empty()) {
		for (auto id = wellid_vec.begin(); id != wellid_vec.end(); id++) {

			well_list_str += "'" + *id + "',";
		}

		well_list_str.pop_back();

		where_wellid_sub = " wellid in (" + well_list_str + ") and ";
	}
	else {
		where_wellid_sub = " wellid in ('" + this->wellid + "') and ";
	}
	
	/*################################################################################################################################################

	
	3. 根据 args 编译为 DataExtract 的 condition 字段,condition 字段包括:
		
		* compare_condition
		* date_condition
		* order_condition
		* final_condition=date_condition+compare_condition+order_condition
		a

	################################################################################################################################################*/
	
	//printf("\ndate_condition %s\n", date_condition.c_str());
	//printf("\ncompare_condition %s\n", compare_condition.c_str());

	/*##########################   3.4 合成 final_condition 字符串  #######################*/
	TidyUpArgs();
	compare_condition = ComposeArgs();
	final_condition += where_wellid_sub+compare_condition + date_condition + order_condition;
			
	printf("thisi final condition %s", final_condition.c_str());


	/*##########################   4 返回最终map映射  #######################*/
	map<string, vector<string>> full_table = this->getFullTable(table_name, par_vec,final_condition);
	
	this->_report_table=full_table;
}

void ProductionBase::addArgs(string col, string operation,string condition) {
	vector<string> args_vec_check;
	for (auto id = col.begin(); id != col.end(); id++) {
		*id = toupper(*id);
	};
	//printf("this is col %s\n", col.c_str());
	
	
	
	if (col.find("DATE") != string::npos) {
		
		if (condition.size() < 11) {
			condition = "to_date('" + condition + " 00:00:00','yyyy/mm/dd hh24:mi:ss')";
		}
		else {
			condition = "to_date('" + condition + "','yyyy/mm/dd hh24:mi:ss')";
		}
	}
	if (!args.empty()) {
		for (auto id = args.begin(); id != args.end(); id++) {
			args_vec_check.push_back(id->first);
			//printf("this is args parameter %s\n", id->first.c_str());
		};
		cout << "this args size\n" << args_vec_check.size() << endl;

		if(VecMemberCheck(args_vec_check, col)) {
			cout << VecMemberCheck(args_vec_check, col) << " "<<col<<endl;
			cout << "insert new" << endl;
			col = col + "_1";
			args[col] = operation + " "+condition+" ";
		}
		else {
			args[col] = operation + " " + condition + " ";
		}
	}
	else {

		args[col] = operation + " " + condition + " ";
	}
	
	
		
}


map<string, string> ProductionBase::getArgs() {
	return this->args;

}

double ProductionBase::ProcessProdData(map<string, vector<string>> well_prod_data,
	initializer_list<pair<string, string>> args) {
	
	//printf("starting to processproddata\n");

	DataProcess data_process;
	string min_date, max_date;
	int min_date_subscript,max_date_subscript;
	vector<int> vec_scope;
	for (auto id = args.begin(); id != args.end(); id++) {
		if (id->first.find("MIN_DATE") != string::npos) {

			//printf("min_date,%s\n",id->second.c_str());
			if (id->second.size() <=11) {
				//printf("id->second +  00:00 : 00");
				min_date = id->second + " 00:00:00'";
			}
			else {
				//printf("id->second ");
				min_date = id->second;
			}
		}
		else if (id->first.find("MAX_DATE") != string::npos) {
			//printf("max_date,%s\n", id->second.c_str());
			//printf("max_date\n");
			if (id->second.size() <=11) {
				max_date = id->second + " 00:00:00'";
			}
			else {
				max_date = id->second;
			}
		}
		else {
				
			//printf("id->second 222");
			min_date = well_prod_data["PRODUCTION_DATE"][0];
				
			auto max_id = well_prod_data["PRODUCTION_DATE"].end();
			max_date= *(max_id-1);

		}
		
	}
	//printf("date: %s,%s\n", min_date.c_str(), max_date.c_str());
	TimeConvert str2time;
	if (!min_date.empty() && !max_date.empty()) {
		
		int i = 0;
		for (auto id = well_prod_data["PRODUCTION_DATE"].begin(); id != well_prod_data["PRODUCTION_DATE"].end(); id++) {
			

			if (str2time.StringToTime(*id)>=str2time.StringToTime(min_date) 
				&& 
				str2time.StringToTime(*id)<=str2time.StringToTime(max_date)) {
				
				min_date_subscript = i;
				
				vec_scope.push_back(i);
			}
			
			i++;
		}
	}
	//printf("starting to calculate casing pressure....\n");
	auto final_avg = data_process.DataAvg("CASING_PRESSURE", well_prod_data, vec_scope);
	//double final_avg = 0.1;
	return final_avg;
	
}


/*
ProductionBase::InstantToDailyDataProcess
需要优化为通用模板

*/
map<string,string> ProductionBase::InstantToDailyDataProcess(
	string wellid,
	string key_col,
	map<string, map<string, vector<string>>> prod_table,

	initializer_list<pair<string, string>> args) {
	/*
	################################################################################
	1.wellid（或Key value)
	2.需要进行操作的列
	3.操作列的计算条件，如（时间范围，数值范围等...)
	4.返回的是map 类型，包括wellid，操作列名以及最终值	
	################################################################################
	*/
	//printf("UpdateBetweenInstantToDaily...");
	
	TimeConvert ST;
	string min_date_string, max_date_string;
	string prod_date_string, prod_time;
	string operation;
	time_t prod_date,min_date,max_date;
	map<string, string> where_sub;
	string condition_string,return_key_value;

	auto id = args.begin();
	while (id != args.end()) {

		if (id->first.find("DATE") != string::npos) {
			prod_date_string = id->second;
		}
		 if (id->first.find("TIME") != string::npos) {
			prod_time = id->second;
		}
		 if (id->first.find("OPERATION") != string::npos) {
			 operation = id->second;
		}
		 if (id->first.find("CONDITION") != string::npos) {
			 condition_string += " and "+id->second+" ";
		 }


		id++;
	}

	if (prod_time.empty()) {
		prod_date = ST.StringToTime(prod_date_string);
		min_date = prod_date + 8 * 60 * 60;
		min_date_string = ST.TimeToString(min_date);
	}
	else {

		min_date_string = prod_date_string;

	}
	
	max_date = min_date + 24 * 60 * 60;
	max_date_string = ST.TimeToString(max_date);

	if (operation == "AVERAGE") {
		double avg=ProcessProdData(prod_table[wellid],
									{
										{"MIN_DATE",min_date_string},
										{"MAX_DATE",max_date_string}
									}
		);
		

		//printf("%s,%s,%s,%.2lf\n", wellid.c_str(), prod_date_string.c_str(), key_col.c_str(), avg);
		where_sub["KEY_VALUE"] = wellid;
		where_sub["KEY_COL"] = key_col;
		where_sub["CONDITION"] = condition_string;
		where_sub["RETURN_VALUE"] = NumToString(avg);

		return where_sub;

	}
	
}

/*######################################  set & get wellid     ########################################################*/

void ProductionBase::setWellid(string well_id) {
	this->wellid = well_id;

}

/*######################################  set & get Table Name    ########################################################*/
void ProductionBase::setProdTableName(string table_name) {
	this->_table_name = table_name;
	this->setTableName(table_name);
}

string ProductionBase::getTableName() {
	return this->_table_name;
}
/*######################################  set & get columns    ########################################################*/

vector<string> ProductionBase::getColumns() {
	auto table_initial=this->getTableInital();
	vector<string> column_vec = table_initial.GetColumn(this->_table_name);
	return column_vec;
}

void ProductionBase::addParameterVec(string parameter) {
	vector<string> par_vec_check;


	for (auto id = parameter.begin(); id != parameter.end(); id++) {
		*id = toupper(*id);
	};
	
	
		this->par_vec.push_back(parameter);
	}
	
	
vector<string> ProductionBase::getParameterVec() {

	return this->par_vec;

}

void ProductionBase::ArgsClean() {
	TidyUpArgs();
}

void ProductionBase::TidyUpArgs() {
	string compare_condition;
	map<string, string> data_dict_1;
	vector<string> args_vec_1;
	if (args.size() > 0) {
		int final_index;
		auto id = args.begin();
		while (id != args.end()) {


			/*###################################   1.转换 _1 参数的格式为 par_string between (x and x)   #######################*/

			//printf(" tidy up step1...1\n");
			if (id->first.find("_1") != string::npos) {
				//printf(" tidy up step...2\n");
				//printf("this is id->second %s\n", id->second.c_str());
				if (id->second.find("<") != string::npos) {
					int index = id->second.find_first_of("<");
					//printf("this is index %d\n", index);
					////printf("this is id->second[index]\n");
					////printf("%s\n",args[id->first][index]);
					if (args[id->first][index] == '=') {
						final_index = index + 2;
					}
					else {
						final_index = index + 1;
					}
					string max_string;
					for (auto id_sec = id->second.begin() + final_index; id_sec != id->second.end(); id_sec++) {
						max_string += *id_sec;
					};
					data_dict_1[id->first] = " and " + max_string + ")";
					args_vec_1.push_back(id->first);
				}
				
				else if (id->second.find(">") != string::npos) {
					int index = id->second.find_first_of(">");
					
					//printf("this is index2 %d\n", index);
					//printf("this is id->second[index2]\n");
					//printf("%s\n", args[id->first][index]);

					if (args[id->first][index] == '=') {
						final_index = index + 2;
					}
					else {
						final_index = index + 1;
					}
					string min_string;
					for (auto id_sec = id->second.begin() + final_index; id_sec != id->second.end(); id_sec++) {
						min_string += *id_sec;
					};
					int index_par = id->first.find("_1");
					data_dict_1[id->first] = "("+id->first.substr(0,index_par) + " between " + min_string;
					args_vec_1.push_back(id->first);


				
				}
				//printf(" tidy up step...3\n");
			}


			id++;
		}
		};

	/*###################################   2.转换 非_1 参数的格式为 par_string between (x and x)   #######################*/

		//printf(" tidy up step...4\n");

		string par_string;
		string origin_string_max;
		string origin_string_min;
		string final_string_1;
		if (!args_vec_1.empty()) {
			for (auto id = args_vec_1.begin(); id != args_vec_1.end(); id++) {
				int index = id->find("_1");
				par_string = id->substr(0, index);
				printf("this is par_string %s: \n", par_string.c_str());

				if (data_dict_1[*id].find(")") != string::npos) {
					origin_string_max = data_dict_1[*id];
					origin_string_min = "("+par_string + " between  " + args[par_string].substr(1, args[par_string].size() - 1);


					//printf("%s\n", args[par_string].c_str());
				}
				else if (data_dict_1[*id].find("(") != string::npos) {

					origin_string_min = data_dict_1[*id];
					origin_string_max = " and " + args[par_string].substr(1, args[par_string].size() - 1) + " ) ";

				}

				/*###################################   3.组合最终的 par_string between (x and x) ,并删除 _1参数   #######################*/

				args[par_string] = origin_string_min + origin_string_max;
				printf("this is erase id %s\n", id->c_str());
				args.erase(*id);
			}
			
			}
		
	}


	string ProductionBase::ComposeArgs() {
		string condition;
		for (auto id = args.begin(); id != args.end(); id++) {
			printf("this is add args %s", id ->first.c_str());
			condition += id->second+ " and ";

		};
		condition.erase(condition.size()-4, 4);

		printf("this is condition: %s\n", condition.c_str());
		return condition;


}