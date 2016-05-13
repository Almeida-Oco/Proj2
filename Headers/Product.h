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
	static std::string product_file_name;
	static std::map <std::string,double> prod_price;
	
	static Product *P_ptr;
public:
	Product() {};
	Product(const Product &P) {};

	void startUp();

	unsigned int getSize();
	double getPrice(const std::string &product);
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
