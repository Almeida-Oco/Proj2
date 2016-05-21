#include "..\Headers\Bottom_10.h"
#include "..\Headers\Declarations.h"
#include "..\Headers\Trans.h"
#include "..\Headers\Product.h"
#include "..\Headers\Supermarket.h"

using namespace std;

//======================================================================================================================================================
//============================================================ COMPARE FUNCTIONS =======================================================================
//======================================================================================================================================================
bool cmpProdPrice::operator() (const pair < unsigned int, vector < string > >  &P1, const pair < unsigned int, vector <string > > &P2) const
{
	return (Supermarket::Bottom_10::instance()->calcMoney(P1.second) < Supermarket::Bottom_10::instance()->calcMoney(P2.second)) || P1.first == P2.first;
}

bool cmpProdAmount::operator() (const pair<string, unsigned int> &P1, const pair<string, unsigned int> &P2) const
{
	return P2.second < P1.second;
}

//======================================================================================================================================================
//================================================== BOTTOM_10 CLASS METHODS ===========================================================================
//======================================================================================================================================================

void Supermarket::Bottom_10::Source()
{
	string final;
	Bottom_10::CtoT_init();
	if (N_COMMON >= CtoT.size())
	{
		cout << endl << "There are not enough transactions to do a Bottom " << N_COMMON << " reccomendation" << endl;
		return;
	}
	Bottom_10::B10_c_init();
	

	Bottom_10::instance()->initHistogram();

	//print out the recommended products
	cout << "The recommended products are: " << endl;
	final = final + "---> ";
	for (string S : Bottom_10::instance()->bestProd())
		final = final + S + " , ";
	final = final.substr(0, final.length() - 3);
	final = final + " <---";

	cout << final << endl;
}

void Supermarket::Bottom_10::CtoT_init()
{
	CtoT.clear();
	pair<unsigned int, vector<string> > temp_pair;
	vector<string> temp_string;

	//the maximum size of the CtoT vector will be the amount of transactions the info_trans vector contains
	CtoT.reserve(Trans::instance()->getInfo().size());
	//used for more efficient vector::insert

	for (set<Trans_t>::iterator it = Trans::instance()->getInfo().begin(); it != Trans::instance()->getInfo().end(); it++)
	{//merges the products the client bought into a single vector, and pushes it to CtoT
		auto set_it = searchVec(it->number);
		if (set_it == CtoT.end())
			CtoT.push_back(make_pair(it->number, it->products));
		else
			mergeVec(set_it->second, it->products);
	}

	sort(CtoT.begin(), CtoT.end(), cmpProdPrice());
	//when it reaches here the set contains a pair of the client number and the products bought,
	//ordered by the amount of money the client spent at the store
}

void Supermarket::Bottom_10::B10_c_init()
{
	//the maximum number of common products will be the number of products the Bottom 1 client bought
	B10_common.reserve(CtoT.at(0).second.size());
	auto it = CtoT.begin();
	B10_common = it->second;
	it++;
	for (it; it != CtoT.begin() + N_COMMON; it++)
	{
		for (auto vec_it = B10_common.begin(); vec_it != B10_common.end(); vec_it++)
		{
			if (find(it->second.begin(), it->second.end(), *vec_it) == it->second.end())
				vec_it = B10_common.erase(vec_it);
		}
	}
	//now B10_common contains the common products between the Bottom 10
}

void Supermarket::Bottom_10::initHistogram()
{
	auto it = CtoT.begin();  //remember this set is sorted, so the Bottom 10 are the first 10 clients
	advance(it, N_COMMON);		// since they dont matter here, we simply ignore them
	for (it; it != CtoT.end(); it++)
	{
		if (isSimilar(it->second))
		{
			for (auto IT = it->second.begin(); IT != it->second.end(); IT++)
			{//iterate the vector of products the client bought
				if (find(B10_common.begin(), B10_common.end(), *IT) == B10_common.end()) 
				{//meaning it was not bought by all the Bottom 10
					auto hist_it = searchHistogram(*IT);
					if (hist_it == histogram.end())
						histogram.push_back(make_pair(*IT,1)); //if product wasnt already in histogram
					else
						hist_it->second++; //if product was already in histogram
				}
			}
		}

	}
	sort(histogram.begin(), histogram.end(), cmpProdAmount());
}//when it reaches here, the histogram has been created and sorted by descending order

vector<string> Supermarket::Bottom_10::bestProd()
{
	vector<string> bestProds;
	bestProds.reserve(histogram.size());
	const unsigned int NONE = 0;
	unsigned int bought = 0;

	for (auto it = histogram.begin(); it != histogram.end(); it++) 
	{//search the best product in the histogram
		bought = howManyBought(it->first);
		if (bought == NONE)
		{
			bestProds.push_back(it->first);
			auto temp_it = it;
			if ((temp_it+1) != histogram.end() &&  (temp_it+1)->second == it->second)
			{ //done in case there are multiple amount of similar products in the histogram
			 // if there are two products which have 3 repetitions, and 3 repetitions is the max number, then it returns both of them
				bestProds.push_back(temp_it->first);
				temp_it++;
				while (temp_it->second == it->second)
					bestProds.push_back(temp_it->first);
			}
			return bestProds;
		}
		else
			P_amount.push_back(it->second - bought); //created in case histogram recommendation fails
	}
	//if the program gets through this for loop it means that there was no product in the histogram
	//that was not bought by the Bottom 10

	auto max_it = max_element(P_amount.begin(), P_amount.end()); //get the best product
	auto bP_it = histogram.begin();
	for (unsigned int i = 0; i < P_amount.size(); i++)
	{//this is done in case there is a tie between two or more products
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

//======================================================================================================================================================
//================================================== BOTTOM_10 CLASS AUXILIAR METHODS ==================================================================
//======================================================================================================================================================


unsigned int Supermarket::Bottom_10::howManyBought(const string &S) const
{//counts how many times the given product was bought by the bottom 10 clients
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

double Supermarket::Bottom_10::calcMoney(const vector<string> &prods) const
{//calculates the price of the vector of product
	double total = 0;
	for (auto it = prods.begin(); it < prods.end(); it++)
		total = total + Product::instance()->getPrice(*it);

	return total;
}

bool Supermarket::Bottom_10::isSimilar(const vector<string> &candidate_P) const
{//check if the given candidate bought all the bottom 10 common products
	for (auto it = B10_common.begin(); it != B10_common.end(); it++)
		if (find(candidate_P.begin(), candidate_P.end(), *it) == candidate_P.end())
			return false;
	return true;
}

void Supermarket::Bottom_10::mergeVec(vector<string> &V1, const vector<string> &V2)
{ //used to merge vectors together
	for (string S : V2)
		V1.push_back(S);
}

vector < pair < unsigned int, vector <string> > >::iterator Supermarket::Bottom_10::searchVec(unsigned int N)
{  //searches the vector for the given number
	auto it = CtoT.begin();
	for (it; it != CtoT.end(); it++)
		if (it->first == N)
			return it;
	return CtoT.end();
}

vector < pair < string, unsigned int > >::iterator Supermarket::Bottom_10::searchHistogram(const string &S)
{ //searches the given products in the vector
	auto it = histogram.begin();
	for (it; it != histogram.end(); it++)
		if (it->first == S)
			return it;
	return histogram.end();
}

vector< pair < unsigned int, vector< string> > > &Supermarket::Bottom_10::getCtoT()
{
	return CtoT;
}
