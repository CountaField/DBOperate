#pragma once
#include <vector>
#include <sstream>
using namespace std;


template <typename T>
double VecSum(T vec) {
	auto sum=0.0;
	auto id = vec.cbegin();

	while (id != vec.cend()) {
		sum += *id;
		id++ ;
	}
	return sum;

}

template <typename T>
string VecUpper(T vec) {
	for (auto id = vec.begin(); id != vec.end(); id++) {
		*id = toupper(*id);
	}

}

template <typename T>
 double VecAvg(T vec) {
	auto sum=0.0;
	auto avg=0.0;
	sum = VecSum(vec);

	avg = sum / vec.size();

	return avg;
}
 /*############################ 根据提供的值(F VALUE） 找到value在Vector中对应的index并返回index列表 ##################*/
 template <typename T,typename F>
 vector<int> VecFindLoaction(T vec,F value) {
	 int loc=0;
	 vector<int> location_vec;
	 auto id = vec.cbegin();
	 while (id != vec.cend()) {
		 if (*id == value) {
			 location_vec.push_back(loc);
		 }
		 id++;
		 loc++;
	 }
	 
	 return location_vec;
	
 }
 /*#################################################### 删除vector中重复的值 ##########################################*/
 template <typename T>
 T VecRemoveDuplicate(T vec) {
	 T new_vec;
	 auto id = vec.cbegin();
	 while (id != vec.cend()) {
		 auto check = find(new_vec.begin(), new_vec.end(), *id);
		 if (check ==new_vec.end()) {
				 new_vec.push_back(*id);
			 }
		
		
		 id++;
	 }

	 return new_vec;

 }


 template <typename T,typename M>
 int VecMemberCheck(T vec, M mem) {
	 
	 for (auto id = vec.cbegin(); id != vec.cend(); id++) {
		 if (*id == mem) {
	
			 return 1;
		 }	
		 else if (id == vec.cend()-1 && *id!=mem) {
			 return 0;

		 }

	 }
 }

 template <typename T, typename M>
 T SequentialContainerElementRemove(T sequecontainer, M value) {

 }


 


template <class Type>
 Type stringToNum(string str) {

	 istringstream iss(str);
	 Type num;
	 iss >> num;
	 return num;

 }
 
 template <class Type>
 string NumToString(Type num) {

	 ostringstream os;
	 if (os << num)
		 return os.str();
	 return "invalid conversion";
 }


 






