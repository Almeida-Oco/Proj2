#ifndef BOTTOM_10_H
#define BOTTOM_10_H

#include "Supermarket.h"
#include <set>
#include <vector>
#include <string>

const unsigned int N_COMMON = 3;
//change the value for testing purposes, if N_COMMON = 10, then it does Bottom_10, if it is 3, then it does Bottom_3

struct cmpProdPrice
{
	bool operator() (const std::pair < unsigned int, std::vector < std::string > >  &P1, const std::pair < unsigned int, std::vector < std::string > > &P2) const;
};

struct cmpProdAmount
{
	bool operator() (const std::pair<std::string, unsigned int> &P1, const std::pair<std::string, unsigned int> &P2) const;
};

class Supermarket::Bottom_10
{
private:
	/*		   	
	* MEMBERS
	*/
	std::vector< std::pair < unsigned int, std::vector< std::string> > > CtoT;
	std::vector<std::string> B10_common;
	std::vector < std::pair < std::string , unsigned int> > histogram;
	std::vector<int> P_amount;
	static Bottom_10 *B10_ptr;

	/*
	* METHODS
	*/
	void initHistogram();
	std::vector< std::string> bestProd();
	std::vector < std::pair < std::string, unsigned int > >::iterator searchHistogram(const std::string &S);
	bool isSimilar(const std::vector<std::string> &candidate_P) const;
	unsigned int howManyBought(const std::string &S) const;
	void mergeVec(std::vector<std::string> &V1, const std::vector<std::string> &V2);

public: 
	void CtoT_init();
	void Source();
	double calcMoney(const std::vector<std::string> &prods) const;
	std::vector< std::pair < unsigned int, std::vector< std::string> > > &getCtoT();
	std::vector < std::pair < unsigned int, std::vector <std::string> > >::iterator searchSet(unsigned int N);
	void B10_c_init();

	static Bottom_10 *instance()
	{
		if (!B10_ptr)
			B10_ptr = new Bottom_10;
		return B10_ptr;
	}
};

#endif // !1