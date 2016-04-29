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

vector<string> string_split(const string &line, const string spliter);
//similar to java string_split, given a string and a spliter, it returns the different parts of the original string in a vector

string remove_middle_spaces(const string &S);
//leaves only one middle space between the different words there might exist

string trim(string &str);
//removes all spaces at the left and at the right of the string

bool testText(const string &c_name);

class Product {
	static string product_file_name;
	static map <string,double> prod_price;
public:

	//initializes products vector
	Product();
	double getPrice(const string &product);
	string getProd(double price);
	void update();
};

#endif // !PRODUCT_H
