#include "DataExtract.h"



void DataExtract::setTableName(string tname) {

	this->_table_name = tname;

}

void DataExtract::setParameterVec(vector<string> parvec) {
	this->par_vec = parvec;
	
}

void DataExtract::setCondition(vector<string> condvec) {
	
	for (auto id = condvec.cbegin(); id != condvec.cend(); id++) {
		this->condition += *id+ " and ";

	};

}


OracleConn DataExtract::getDBConnection() {

	return this->gsrdb;

}

void DataExtract::ExtractDataByTable(
	
	//vector<string> wellid_vec,
	string table_name,
	vector<string> par_vec,
	string condition) {
	

	/*#######################      1.����ѯ���б�δָ�������ȡ���е������в�ת�����ַ���             ############################*/
	TableExtract table_init;
	string sql_base;
	string par_string;
	if (par_vec.empty()) {

		for (auto id = sql_base.begin(); id != sql_base.end(); id++) {
			*id = toupper(*id);
		}

		par_vec = table_init.GetColumn(table_name);

	}


	for (auto id = par_vec.begin(); id != par_vec.end(); id++) {
		par_string += *id + ",";
	}

	par_string.pop_back();

	
	/*#######################     2. ������Ϊ������ʼ��mapӳ��    #######################*/
	map<string, vector<string>> prod_value_vec;
	for (auto id = par_vec.begin(); id != par_vec.end(); id++) {
		prod_value_vec[*id] = {};

	}

	/*#######################     3.��ʼ��SQL��䣬��ȡ����,����vector�����Ӧ������ӳ����    #######################*/

	sql_base = "select " + par_string + " from " + table_name + " " + condition;
	for (auto id = sql_base.begin(); id != sql_base.end(); id++) {
		*id = toupper(*id);
	}

	char *sql_base_c = (char*)sql_base.data();
	printf("Starting extract Data From Table\n");
	printf("SQL IS: %s\n", sql_base_c);
	system("pause");
	this->gsrdb.StatmentInitial(sql_base_c);
	auto rs = this->gsrdb.rs;
	

	while (rs->next()) {
		int i = 1;
		auto id_par = par_vec.cbegin();
		while (id_par != par_vec.cend()) {
			string insert_value;
			if (id_par->find("DATE") == string::npos) {

				insert_value = rs->getString(i);

			}
			else{
				auto data = rs->getString(i);
				if (!data.empty()) {
					printf("this is the id_par %s\n", id_par->c_str());
					printf("this is the value %s\n", rs->getString(i).c_str());
					insert_value = rs->getDate(i).toText("yyyy/mm/dd hh24:mi:ss");
				}
				
			}

			if (insert_value.empty()) {
				insert_value = "null";
			}
			prod_value_vec[*id_par].push_back(insert_value);
			id_par++;
			i++;
		}
	}
	/*#######################     4.����MAPӳ��    #######################*/
	/*this->_table_name = table_name;
	this->par_vec = par_vec;
	this->condition = condition;*/
	this->gsrdb.EndConn();
	this->full_table=prod_value_vec;

}



void DataExtract::TidyUpDataByKeyCol(
	map <string, vector<string>> prod_data_map,
	string key_col)
{
	
	vector<string> col_vec;
	map<string, map<string, vector<string>>> final_prod_data;
	map<string, vector<string>> col_data_map;
	string col;

	/*###############################################################################################################################
	
	1.�����������ݣ���ʼ���ؼ������б������йؼ��ַ���col_vec������ȥ�ز�����VecRemoveDuplicate��
	
									ȥ�ز����� ComputerTools.h�ж���
	
	################################################################################################################################*/
	for (auto id = prod_data_map.begin(); id != prod_data_map.end(); id++) {
		if (id->first != key_col) {
			col_vec.push_back(id->first);
		}
	}

	auto key_col_vec = VecRemoveDuplicate(prod_data_map[key_col]);



	/*###############################################################################################################################
	
	2.���ݹؼ����б� col_vec�����ؼ���ӳ�䣬������ؼ����йص����ݴ������ԭʼ����prod_data_map���г����������ؼ���col��ص�����ӳ��col_data_map[col]�У�
	����colΪ���ؼ�������������е��������ؼ��������ݹ�ϵ��ͨ����һ���������б�õ��ģ���󷵻�����ӳ��final_prod_data,���ֵΪ�ؼ���
	################################################################################################################################*/

	for (auto id = key_col_vec.begin(); id != key_col_vec.end(); id++) {
		printf("looping %s...\n",col);
		//��ʼѭ���ؼ����б� col_vec

		auto key_col_loc = VecFindLoaction(prod_data_map[key_col], *id);

		for (auto id_col = prod_data_map.begin(); id_col != prod_data_map.end(); id_col++) {
			printf("looping collumns...\n");
			//ѭ�������ݣ���ʼ���뵱ǰѭ���ؼ�����ص�����ӳ��col_data_map[col]������colΪ���ؼ�������������е�����
			if (id_col->first != key_col) {
				col = id_col->first;
			}
			else {
				continue;
			}
			col_data_map[col] = {};
			for (auto id_loc = key_col_loc.begin(); id_loc != key_col_loc.end(); id_loc++) {
				printf("looping index...%s , %s , %s\n", id->c_str(), col.c_str(), prod_data_map[col][*id_loc].c_str());
				//��ʼѭ���½Ǳ꣬��ؼ�����ص����ݶ���ͨ����һ���ҵ��ؼ����б��index�Ӷ��Ӹ��Ե��б��и���indexһһ��ȡ������


				col_data_map[col].push_back(prod_data_map[col][*id_loc]);
			}//�½Ǳ�ѭ������
		}//������ѭ������

		final_prod_data[*id] = col_data_map;
	}//����ѭ������
	//��󷵻�����ӳ��final_prod_data, ���ֵΪ�ؼ���
	this->convert_table=final_prod_data;


}


map<string, vector<string>> DataExtract::getFullTable(string table_name,
	vector<string> par_vec,
	string condition) {
	if (this->full_table.empty()) {
		this->ExtractDataByTable(table_name, par_vec, condition);
		return full_table;
	}
	else
		return full_table;

}



map<string, map<string, vector<string>>> DataExtract::getConvertTableByKeyCol(
	map <string, vector<string>> prod_data_map,
	string key_col) {

	if (this->convert_table.empty()) {

		this->TidyUpDataByKeyCol(prod_data_map, key_col);
		return convert_table;
	}
	else
		return convert_table;

}


vector<string> DataExtract::getTableColumn() {

	vector<string> table_column=this->tb_extract.GetColumn(this->_table_name);
	return table_column;
}

TableExtract DataExtract::getTableInital() {
	return this->tb_extract;
}