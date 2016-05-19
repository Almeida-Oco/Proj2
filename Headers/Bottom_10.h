#ifndef BOTTOM_10_H
#define BOTTOM_10_H

#include "Supermarket.h"
#include <vector>
#include <string>

const unsigned int N_COMMON = 3;
//change the value for testing purposes, if N_COMMON = 10, then it does Bottom_10, if it is 3, then it does Bottom_3

struct cmpProdPrice //used to compare the amount of money a client has spent
{
	bool operator() (const std::pair < unsigned int, std::vector < std::string > >  &P1, const std::pair < unsigned int, std::vector < std::string > > &P2) const;
};

struct cmpProdAmount //used to sort the histogram by number of products bought by descending order
{
	bool operator() (const std::pair<std::string, unsigned int> &P1, const std::pair<std::string, unsigned int> &P2) const;
};

class Supermarket::Bottom_10
{
private:
	/*		   	
	* DATA MEMBERS
	*/
	std::vector< std::pair < unsigned int, std::vector< std::string> > > CtoT; 
	//matches the client to all the products he bought
	std::vector<std::string> B10_common;
	//will hold the common products between the bottom 10
	std::vector < std::pair < std::string , unsigned int> > histogram;
	//correlates products to its amount of occurrences
	std::vector<int> P_amount;
	//used in case all products in the histogram have been bought by at least 1 Bottom 10
	static Bottom_10 *B10_ptr;

	/*
	*  MAIN MEMBER FUNCTIONS
	*/
	void initHistogram(); //needs to first have CtoT initialized
	std::vector< std::string> bestProd(); //returns vector of the recommended products
	
	/*
	* AUXILIARY MEMBER FUNCTIONS
	*/

	unsigned int howManyBought(const std::string &S) const;
	void mergeVec(std::vector<std::string> &V1, const std::vector<std::string> &V2);
	bool isSimilar(const std::vector<std::string> &candidate_P) const;
	std::vector < std::pair < std::string, unsigned int > >::iterator searchHistogram(const std::string &S);

public: 

	Bottom_10() {};
	Bottom_10(const Bottom_10 &C) {};

	/*
	*  MAIN MEMBER FUNCTIONS
	*/
	void CtoT_init(); 
	void Source();//it is the main function in the bottom_10 class
	void B10_c_init();//gathers the common Bottom 10 products
	/*
	* AUXILIARY MEMBER FUNCTIONS
	*/
	double calcMoney(const std::vector<std::string> &prods) const;
	std::vector< std::pair < unsigned int, std::vector< std::string> > > &getCtoT();
	std::vector < std::pair < unsigned int, std::vector <std::string> > >::iterator searchVec(unsigned int N);
	

	static Bottom_10 *instance()
	{
		if (!B10_ptr)
			B10_ptr = new Bottom_10;
		return B10_ptr;
	}
};

#endif // !1