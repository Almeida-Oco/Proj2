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
	static Visualize *V_pt;

public:
	Visualize() {};
	Visualize(const Visualize &V) {};

	void visProd(const string &prod) const;
	void visNumber(unsigned int number) const; //WORKING
	void visName(const string &name) const; //WORKING
	map<int, string> visAllProd() const;
	//creates a map that associates a number to the product name (used for new transactions)
	string P_comma(const vector<string> &prods);
	//given a vector of strings(products) it returns it with commas
	// { "pao" , "arroz" } --> "pao, arroz"

	static Visualize *instance()
	{
		if (!V_pt)
			V_pt = new Visualize;
		return V_pt;
	}
};

#endif // !VISUALIZE_H
