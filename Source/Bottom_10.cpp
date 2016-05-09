#include "..\Headers\Bottom_10.h"
#include "..\Headers\Declarations.h"
#include "..\Headers\Trans.h"
#include "..\Headers\Product.h"
#include "..\Headers\Supermarket.h"
class Supermarket;
class Trans;
std::map<unsigned int, std::vector< std::string> > Supermarket::Bottom_10::CtoP;
std::vector<std::string> Supermarket::Bottom_10::B10_common;
std::map < std::string, unsigned int > Supermarket::Bottom_10::histogram;


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
	sort(CtoP.begin(), CtoP.end(), [&](const std::pair< unsigned int, std::vector<std::string> > &T1, const std::pair< unsigned int, vector<std::string> > &T2) -> bool {return (calcMoney(T1.second) < calcMoney(T2.second)); }); //falta testar, mas em principio deve dar
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
	double total = 0;
	for (auto it = prods.begin(); it < prods.end(); it++)
		total = total + Product::instance()->getPrice(*it);

	return total;
}

bool Supermarket::Bottom_10::cmpPairTrans(const std::pair< unsigned int, std::vector<std::string> > &T1, const std::pair< unsigned int, vector<std::string> > &T2) const
{
	return ( calcMoney(T1.second) < calcMoney(T2.second) );
}

void Supermarket::Bottom_10::initHistogram()
{
	auto it = CtoP.begin();  //remember this map is sorted, so the Bottom 10 are the first 10 clients
	advance(it, 10);		// since they dont matter here, we simply ignore them
	for (it; it != CtoP.end(); it++)
	{
		if (isSimilar(it->second))
		{
			for (auto IT = it->second.begin(); IT != it->second.end(); IT++)
			{

				if (find(B10_common.begin(), B10_common.end(), *IT) == B10_common.end()) //meaning it was not bought by all the Bottom 10
					histogram[*IT]++;
			}
		}

	}
	sort(histogram.begin(), histogram.end(), [&](const pair< string, unsigned int> &P1, const pair<string, unsigned int> &P2) -> bool {return P1.second > P2.second;} );
}//when it reaches here, the histogram has been created and sorted by descending order

bool Supermarket::Bottom_10::isSimilar(const std::vector<std::string> &candidate_P) const
{
	for (auto it = B10_common.begin(); it != B10_common.end(); it++)
		if (find(candidate_P.begin(), candidate_P.end(), *it) == candidate_P.end())
			return false;
	return true;
}