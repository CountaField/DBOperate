#include "Oracle_Connection.h"
/*#include <string>
#include <iostream>
#include "occi.h"*/
#include <typeinfo>


using namespace std;
using namespace oracle::occi;

OracleConn::OracleConn() {
	OracleConn::EnvCreate();
	Statement::Status status = stmt->status();
	//string OracleConn::connstr = "10.59.37.13:1521/gsrbk";
};



 inline auto OracleConn::EnvCreate(string u, string p) {	 	
	printf("Starting create environment USING CUST PAR.....\n");
	env = Environment::createEnvironment();
	cout << "Connecting Database.... " << connstr << endl;
	conn = env->createConnection(u, p, connstr);
	printf("Connection Successful!\n");
	stmt = conn->createStatement();
	return conn;
}
 
 inline void OracleConn::EnvCreate() {
	 printf("Starting create environment WITHOUT CUST PAR.....\n");
	 env = Environment::createEnvironment();
	 cout << "Connecting Database.... " << connstr << endl;	
	 conn = env->createConnection(userid,password, connstr);
	 printf("Connection Successful!\n");
	 stmt = conn->createStatement();
	 //return OracleConn::conn;
 }
 void OracleConn::StatmentInitial(char* sql) {
	 
	 //Statement::Status status =stmt->status(); //Unprepared Statut (Create statement without SQL)
	 stmt->setSQL(sql);
	 stmt->execute();
	 rs = stmt->getResultSet();
	 //return OracleConn::rs;
 }

 void OracleConn::Update(char *sql) {
	 //Statement::Status status = stmt->status(); //Unprepared Statut (Create statement without SQL)
	 stmt->setSQL(sql);
	 stmt->executeUpdate();
 };

void OracleConn::EndConn() {
	 env->terminateConnection(conn);
	 Environment::terminateEnvironment(env);	 
 }



