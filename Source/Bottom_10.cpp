#include "..\Headers\Bottom_10.h"
#include "..\Headers\Declarations.h"
#include "..\Headers\Product.h"
#include "..\Headers\Supermarket.h"
class Supermarket;
class Trans;
std::map<unsigned int, std::vector< std::string> > Supermarket::Bottom_10::CtoP;
std::vector<unsigned int> Supermarket::Bottom_10::B_10;
std::vector<std::string> Supermarket::Bottom_10::B10_common;

void Supermarket::Bottom_10::startUp()
{
	//creates CtoP, key is the Client number, value is a vector of the products the client bought
	for (auto it = Trans::instance()->getInfo().begin(); it != Trans::instance()->getInfo().end(); it++)
	{
		if (!search_map(it->number))
			CtoP[it->number] = it->products;
		else
			CtoP[it->number].insert(  CtoP[it->number].end(), it->products.begin(), it->products.end() );
	}
	sort(CtoP.begin(), CtoP.end(), cmpPair); //falta testar, mas em principio deve dar
	//se der entao o primeiro elemento do map deve ser o que fez menos compras, pelo que os bottom 10 sao os 10 primeiros elementos

	auto it = CtoP.begin();
	B10_common = it->second;
	advance(it, 1);
	for (it; it != CtoP.end(); it++)
	{
		for (string S : B10_common)
		{//searches for B10_common products in the vector of products, and if they are not found, meaning it is not a common product
			//between the Bottom 10, it erases that product from B10_common
			if (find(it->second.begin(), it->second.end(), S) == it->second.end())
				B10_common.erase(find(B10_common.begin(), B10_common.end(), S));
		}
	}

}//once this method ends, CtoP relates the client to the products it bought and it is sorted, meaning the first 10 clients are the Bottom 10
//B10_common will hold the common products between the Bottom 10

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
	double total;
	for (auto it = prods.begin(); it < prods.end(); it++)
		total += Product::instance()->getPrice(*it);

	return total;
}

bool Supermarket::Bottom_10::cmpPair(pair< unsigned int, vector<string> > P1, pair< unsigned int, vector<string> > P2)
{
	return ( calcMoney(P1.second) < calcMoney(P2.second) );
}