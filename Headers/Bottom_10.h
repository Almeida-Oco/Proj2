#ifndef BOTTOM_10_H
#define BOTTOM_10_H

#include "Supermarket.h"
#include "Trans.h"
#include <map>
#include <vector>
#include <string>

class Supermarket::Bottom_10
{
private:
	static std::map<unsigned int, std::vector< std::string> > CtoP;
	static std::map<unsigned int, double > CtoM;
	static std::vector<unsigned int> B_10;
	static std::vector<std::string> B10_common;

	bool search_map(unsigned int K) const;
	double calcMoney(const std::vector<std::string> &prods) const;
public: 
	static Bottom_10 *B10_ptr;
	bool cmpPair(std::pair< unsigned int, std::vector<std::string> > P1, std::pair< unsigned int, vector<std::string> > P2);
	void startUp();


	static Bottom_10 *instance()
	{
		if (!B10_ptr)
			B10_ptr = new Bottom_10;
		return B10_ptr;
	}
};

#endif // !1