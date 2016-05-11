#ifndef BOTTOM_10_H
#define BOTTOM_10_H

#include "Supermarket.h"
#include <set>
#include <vector>
#include <string>

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
	static std::vector< std::pair < unsigned int, std::vector< std::string> > > CtoT;
	static std::vector<std::string> B10_common;
	static std::vector < std::pair < std::string , unsigned int> > histogram;
	static std::vector<int> P_amount;
	
	static Bottom_10 *B10_ptr;

	
	void startUp();
	void initHistogram();
	std::vector< std::string> bestProd();
	std::vector < std::pair < unsigned int, std::vector <std::string> > >::iterator searchSet(unsigned int N);
	std::vector < std::pair < std::string, unsigned int > >::iterator searchHistogram(const std::string &S);
	bool isSimilar(const std::vector<std::string> &candidate_P) const;
	unsigned int howManyBought(const std::string &S) const;
	void mergeVec(std::vector<std::string> &V1, const std::vector<std::string> &V2);

public: 
	void Source();
	double calcMoney(const std::vector<std::string> &prods) const;
	static Bottom_10 *instance()
	{
		if (!B10_ptr)
			B10_ptr = new Bottom_10;
		return B10_ptr;
	}
};

#endif // !1