#ifndef PRODUCT_H
#define PRODUCT_H
#include "Supermarket.h"
#include "Declarations.h"
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Supermarket::Product
{
	static string product_file_name;
	static map <string,double> prod_price;
	
	static Product *P_ptr;
public:

	//initializes products vector
	Product() {};
	Product(const Product &P) {};

	void startUp();

	unsigned int getSize();
	double getPrice(const string &product);
	string getProd(unsigned int position);
	void update();

	static Product *instance()
	{
		if (!P_ptr)
			P_ptr = new Product;
		return P_ptr;
	}
};

#endif // !PRODUCT_H
