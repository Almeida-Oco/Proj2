#include "..\Headers\Bottom_10.h"
#include "..\Headers\Declarations.h"
#include "..\Headers\Trans.h"
#include "..\Headers\Product.h"
#include "..\Headers\Supermarket.h"

class Supermarket;
class Trans;

std::set< std::pair < unsigned int, std::vector< std::string> >, cmpProdPrice > Supermarket::Bottom_10::CtoT;
std::vector<std::string> Supermarket::Bottom_10::B10_common;
std::vector<int> Supermarket::Bottom_10::P_amount;
std::vector < std::pair < std::string, unsigned int> > Supermarket::Bottom_10::histogram;

//======================================================================================================================================================
//============================================================ COMPARE FUNCTIONS =======================================================================
//======================================================================================================================================================
bool cmpProdPrice::operator() (const std::pair < unsigned int, std::vector < std::string > >  &P1, const std::pair < unsigned int, std::vector < std::string > > &P2) const
{
	return (Supermarket::Bottom_10::instance()->calcMoney(P1.second) < Supermarket::Bottom_10::instance()->calcMoney(P2.second)) || P1.first == P2.first;
}

bool cmpProdAmount::operator() (const std::pair<std::string, unsigned int> &P1, const std::pair<std::string, unsigned int> &P2) const
{
	return P2.second < P1.second;
}

//======================================================================================================================================================
//================================================== BOTTOM_10 CLASS METHODS ===========================================================================
//======================================================================================================================================================

void Supermarket::Bottom_10::Source()
{
	string final;
	Bottom_10::instance()->startUp();
	Bottom_10::instance()->initHistogram();

	final = final + "----> ";
	for (string S : Bottom_10::instance()->bestProd())
		final = final + S + " , ";
	final = final.substr(0, final.length() - 3);
	final = final + " <----";
	cout << final << endl;
}

void Supermarket::Bottom_10::startUp()
{
	pair<unsigned int, vector<string> > temp_pair;
	vector<string> temp_string;

	for (vector<Trans_t>::iterator it = Trans::instance()->getInfo().begin(); it != Trans::instance()->getInfo().end(); it++)
	{
		auto set_it = searchSet(it->number);
		if (set_it ==  CtoT.end())
			CtoT.insert(make_pair(it->number, it->products));
		else
		{
			temp_string = it->products;
			mergeVec(temp_string, set_it->second);
			temp_pair = make_pair(set_it->first, temp_string);
			CtoT.erase(set_it);
			if (CtoT.size() == 0)
				CtoT.insert(temp_pair);
			else
				CtoT.insert(set_it, temp_pair);
		}
	}//when it reaches here the set contains a pair of the client number and the products bought,
	//ordered by the amount of money the client spent at the store

	auto it = CtoT.begin();
	auto it_end = CtoT.begin();
	advance(it_end, 3);
	B10_common = it->second;
	advance(it, 1);
	for (it; it != it_end; it++)
	{ // ---------------------------------------------------------------------------------------------------------------> Verificar se depois de se apagar o elemento se o apontador atualiza ou é preciso subtrair 1
		for (auto vec_it = B10_common.begin(); vec_it != B10_common.end(); vec_it++)
		{
			if (find(it->second.begin(), it->second.end(), *vec_it) == it->second.end())
				B10_common.erase(vec_it);
		}
	}
	//now B10_common contains the common products between the Bottom 10
}

void Supermarket::Bottom_10::initHistogram()
{
	auto it = CtoT.begin();  //remember this set is sorted, so the Bottom 10 are the first 10 clients
	advance(it, 3);		// since they dont matter here, we simply ignore them
	for (it; it != CtoT.end(); it++)
	{
		if (isSimilar(it->second))
		{
			for (auto IT = it->second.begin(); IT != it->second.end(); IT++)
			{
				if (find(B10_common.begin(), B10_common.end(), *IT) == B10_common.end()) //meaning it was not bought by all the Bottom 10
				{
					auto hist_it = searchHistogram(*IT);
					if (hist_it == histogram.end())
						histogram.push_back(make_pair(*IT,1));
					else
						hist_it->second++;
				}
			}
		}

	}
	sort(histogram.begin(), histogram.end(), cmpProdAmount());
}//when it reaches here, the histogram has been created and sorted by descending order

vector<string> Supermarket::Bottom_10::bestProd()
{
	vector<string> bestProds;
	const unsigned int NONE = 0;
	unsigned int bought = 0;

	for (auto it = histogram.begin(); it != histogram.end(); it++)
	{
		bought = howManyBought(it->first);
		if (bought == NONE)
		{
			bestProds.push_back(it->first);
			return bestProds;
		}
		else
			P_amount.push_back(it->second - bought);
	}
	//if the program gets through this for loop it means that there was no product in the histogram
	//that was not bought by the Bottom 10

	auto max_it = max_element(P_amount.begin(), P_amount.end());
	auto bP_it = histogram.begin();
	for (unsigned int i = 0; i < P_amount.size(); i++)
	{
		if (P_amount.at(i) == *max_it)
		{
			bP_it = histogram.begin();
			advance(bP_it, i);
			bestProds.push_back(bP_it->first);
		}
	}
	//once it gets here bestProds holds the products to be returned
	return bestProds;
}


unsigned int Supermarket::Bottom_10::howManyBought(const string &S) const
{
	unsigned int cont = 0;
	auto B10_it = CtoT.begin();
	advance(B10_it, 3);

	for (auto it = CtoT.begin(); it != B10_it; it++)
	{
		for (string str : it->second)
		{
			if (str == S)
				cont++;
		}
	}
	return cont;
}

double Supermarket::Bottom_10::calcMoney(const std::vector<std::string> &prods) const
{
	double total = 0;
	for (auto it = prods.begin(); it < prods.end(); it++)
		total = total + Product::instance()->getPrice(*it);

	return total;
}

bool Supermarket::Bottom_10::isSimilar(const std::vector<std::string> &candidate_P) const
{
	for (auto it = B10_common.begin(); it != B10_common.end(); it++)
		if (find(candidate_P.begin(), candidate_P.end(), *it) == candidate_P.end())
			return false;
	return true;
}

void Supermarket::Bottom_10::mergeVec(vector<string> &V1, const vector<string> &V2)
{
	for (string S : V2)
		V1.push_back(S);
}

std::set < std::pair < unsigned int, std::vector <std::string> > >::iterator Supermarket::Bottom_10::searchSet(unsigned int N)
{
	auto it = CtoT.begin();
	for (it; it != CtoT.end(); it++)
		if (it->first == N)
			return it;
	return CtoT.end();
}

std::vector < std::pair < string, unsigned int > >::iterator Supermarket::Bottom_10::searchHistogram(const string &S)
{
	auto it = histogram.begin();
	for (it; it != histogram.end(); it++)
		if (it->first == S)
			return it;
	return histogram.end();
}
