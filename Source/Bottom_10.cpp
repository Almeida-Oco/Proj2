#include "..\Headers\Bottom_10.h"
#include "..\Headers\Declarations.h"
#include "..\Headers\Supermarket.h"
class Supermarket;
class Trans;
std::map<unsigned int, std::vector< std::string> > Supermarket::Bottom_10::CtoP;
std::vector<unsigned int> Supermarket::Bottom_10::B_10;

void Supermarket::Bottom_10::startUp()
{
	vector<Trans_t>::iterator it;
	//creates CtoP, key is the Client number, value is a vector of the products the client bought
	for (it = Trans::instance()->getInfo().begin(); it != Trans::instance()->getInfo().end(); it++)
	{
		if (!search_map(it->number))
			CtoP[it->number] = it->products;
		else
			CtoP[it->number].insert(  CtoP[it->number].end(), it->products.begin(), it->products.end() );
	}

	// creates CtoM, key is client, value is the total amount of money bought
	for (auto it = CtoP.begin(); it != CtoP.end(); it++)
	{
		
	}
}

bool Supermarket::Bottom_10::search_map(unsigned int K) const
{
	for (auto it = CtoP.begin(); it != CtoP.end(); it++)
	{
		if (it->first == K)
			return true;
	}
	return false;
}

double Supermarket::Bottom_10::calcMoney(const std::vector<string> &prods) const
{
	return 0.0;
}
/*
double Supermarket::Bottom_10::getPrice(const std::string &P) const
{
	for (auto it = Product_ptr->)
}*/