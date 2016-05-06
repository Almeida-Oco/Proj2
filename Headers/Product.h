#ifndef PRODUCT_H
#define PRODUCT_H
#include "Input_Asker.h"
#include "Declarations.h"
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Product {
	static string product_file_name;
	static map <string,double> prod_price;
	
	static Product *P_pt;
public:

	//initializes products vector
	Product();

	unsigned int getSize();
	double getPrice(const string &product);
	string getProd(unsigned int position);
	void update();

	static Product *instance()
	{
		if (!P_pt)
			P_pt = new Product;
		return P_pt;
	}
};

#endif // !PRODUCT_H
