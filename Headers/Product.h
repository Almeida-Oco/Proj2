#ifndef PRODUCT_H
#define PRODUCT_H
#include "..\Headers\Input_Asker.h"
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;


//====================================================================================
//=================================== PROTOTYPES ======================================
//====================================================================================
vector<string> string_split(const string &line, const string spliter);
string remove_middle_spaces(const string &S);
string trim(string &str);
bool testText(const string &c_name);


//=================================================================================
//=================================== CLASS ======================================
//=================================================================================
class Product {
	static string product_file_name;
	static map <string,double> prod_price;
public:

	//initializes products vector
	Product();

	unsigned int getSize();
	double getPrice(const string &product);
	string getProd(unsigned int position);
	void update();
};

#endif // !PRODUCT_H
