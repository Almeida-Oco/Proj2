#ifndef VISUALIZE_H
#define VISUALIZE_H

#include "Supermarket.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Product;

class Supermarket::Visualize
{
	static Visualize *V_ptr;

public:
	Visualize() {};
	Visualize(const Visualize &V) {};

	void visProd(const std::string &prod) const;
	void printRecommended(const std::vector<std::string> &P) const;
	void visNumber(unsigned int number) const; //WORKING
	void visName(const std::string &name) const; //WORKING
	std::map<int, std::string> visAllProd() const;
	//creates a map that associates a number to the product name (used for new transactions)
	std::string P_comma(const std::vector<std::string> &prods);
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
