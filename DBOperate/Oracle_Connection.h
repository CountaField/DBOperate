#pragma once

#include <string>;
#include <iostream>;
#include "occi.h";

using namespace std;
using namespace oracle::occi;

class OracleConn {
public:
	
	OracleConn();
	OracleConn(string u, string p) :
		userid(u), password(p) {};
	OracleConn(string u) :userid(u) {};
	//using OracleConn::*env;
	ResultSet *rs;
	Environment *env;
	Statement *stmt;
	Connection *conn;
	void OracleConn::EnvCreate();
	auto OracleConn::EnvCreate(string u, string p);
	void OracleConn::StatmentInitial(char *sql);
	void OracleConn::Update(char *sql);
	void OracleConn::EndConn();
	

protected:
	string  userid = "gsrdba";
	string password = "oracle";
	string connstr = "10.59.37.13:1521/gsrbk";
	//static string connstr ;
	
	
};

