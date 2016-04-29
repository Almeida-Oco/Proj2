#ifndef VISUALIZE_H
#define VISUALIZE_H

#include "..\Headers\Declarations.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "..\Headers\Product.h"

using namespace std;
class Product;
class Visualize
{
public:
	void visProd(string &prod);
	void visNumber(unsigned int number); //WORKING
	void visName(string &name); //WORKING
	map<int, string> visAllProd(Product &P);
	//creates a map that associates a number to the product name (used for new transactions)
	string P_comma(const vector<string> &prods);
	//given a vector of strings(products) it returns it with commas
	// { "pao" , "arroz" } --> "pao, arroz"
};

#endif // !VISUALIZE_H
