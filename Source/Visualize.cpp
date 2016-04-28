#include "Visualize.h"

string Visualize::P_comma(const vector<string> &prods)
{
	string final;
	for (string S : prods)
		final = final + S + ", ";
	return final.substr(0,final.length() -2);
}

//====================================================================================
void Visualize::visNumber(unsigned int number) {
	cout << setw(NUM_BOX) << left << number;
}

//====================================================================================
void Visualize::visName(string &name) {
	cout << setw(NAME_BOX) << left << name;
}

//====================================================================================
void Visualize::visProd(string &prod) {
	cout << setw(PROD_BOX) << left << prod;
}
