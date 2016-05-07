#include "..\Headers\Visualize.h"
#include "..\Headers\Declarations.h"
#include "..\Headers\Product.h"
#include "..\Headers\Supermarket.h"

class Supermarket;

string Supermarket::Visualize::P_comma(const vector<string> &prods)
{
	string final;
	for (string S : prods)
		final = final + S + ", ";
	return final.substr(0,final.length() -2);
}

//====================================================================================
void Supermarket::Visualize::visNumber(unsigned int number) const {
	cout << setw(NUM_BOX) << left << number;
}

//====================================================================================
void Supermarket::Visualize::visName(const string &name) const {
	cout << setw(NAME_BOX) << left << name;
}

//====================================================================================
void Supermarket::Visualize::visProd(const string &prod) const {
	cout << setw(PROD_BOX) << left << prod;
}
//====================================================================================
map<int, string> Supermarket::Visualize::visAllProd() const
{
	unsigned int i = 0, sz = Product::instance()->getSize(); //Product::instance()->getSize();
	map<int, string> n_prod;
	for (i; i < sz; i++)
	{
		cout << i + 1 << " -> " << Product::instance()->getProd(i) << endl;
		n_prod[i+1] = Product::instance()->getProd(i);
	}
	cout << "---> ";
	return n_prod;
}
