#ifndef BOTTOM_10_H
#define BOTTOM_10_H

#include "Supermarket.h"
#include <map>
#include <vector>
#include <string>

class Supermarket::Bottom_10
{
private:
	static std::map<unsigned int, std::vector< std::string> > CtoP;
	static std::vector<std::string> B10_common;
	static std::map < std::string, unsigned int > histogram;
	
	bool search_map(unsigned int K) const;
	static Bottom_10 *B10_ptr;
	double calcMoney(const std::vector<std::string> &prods) const;
	bool cmpPairTrans(const std::pair< unsigned int, std::vector<std::string> > &T1,const std::pair< unsigned int, std::vector<std::string> > &T2) const;
	void startUp();
	void initHistogram();
	bool isSimilar(const std::vector<std::string> &candidate_P) const;
	bool cmpPairProds(const std::pair<std::string, unsigned int> &P1,const std::pair<std::string, unsigned int> &P2);

public: 


	static Bottom_10 *instance()
	{
		if (!B10_ptr)
			B10_ptr = new Bottom_10;
		return B10_ptr;
	}
};

#endif // !1