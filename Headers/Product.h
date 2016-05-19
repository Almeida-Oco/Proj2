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

class Supermarket::Product
{
	std::string product_file_name;
	std::map <std::string,double> prod_price;
	
	static Product *P_ptr;
public:
	//used to avoid multiple class objects
	Product() {};
	Product(const Product &P) {};

	void startUp();

	unsigned int getSize();
	double getPrice(const std::string &product);
	double getPrice(const std::vector<std::string> &product);
	std::string getProd(unsigned int position);
	void update();

	static Product *instance()
	{
		if (!P_ptr)
			P_ptr = new Product;
		return P_ptr;
	}
};

#endif // !PRODUCT_H
