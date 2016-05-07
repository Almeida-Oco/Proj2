#ifndef VISUALIZE_H
#define VISUALIZE_H

#include "Supermarket.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
class Product;

class Supermarket::Visualize
{
	static Visualize *V_ptr;

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
		if (!V_ptr)
			V_ptr = new Visualize;
		return V_ptr;
	}
};

#endif // !VISUALIZE_H
