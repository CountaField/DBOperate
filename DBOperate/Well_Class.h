#pragma once

#ifndef _WELL_BASE_H
#define _WELL_BASE_H


#include <time.h>
#include <iostream>
#include <vector>
#include "Production_Base.h"
#include "DataExtract.h"

using namespace std;




class WellClass {
public:
	WellClass() {
		OracleConn();
	};
	WellClass(const string s) : well_id(s) {
		
	};


private:
	
	string well_id;
	string cluster_id;
	string prod_start_date;
	bool connect_to_prod;
	bool vs_type;
	string orifice_plate_size;
	
	//ProductionBase Prod(string well_id);





protected:




};

#endif