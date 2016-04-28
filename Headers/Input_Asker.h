#ifndef INPUT_ASKER_H
#define INPUT_ASKER_H

#include <vector>
#include <iostream>
#include <string>
#include "Declarations.h"
#include "Visualize.h"
#include "Client.h"

using namespace std;
class Product;
class Client;

class Input_Asker {
public:
	int ask_c_number(const Client &C);
	//asks for a client number until an existing one is entered

	Date_t askDate(int question);
	//input a date using different cout (depending on int question),
	//validates the date and returns the Date struct

	//vector<string> askProducts(Product &P);
	//keeps asking user for products (only existing ones in the Product.txt), until it enters CTRL+Z

	int askClientName(const vector<Client_t> &info_c);
	//keeps asking client name until an existing one is entered

	string askProduct();
	//aks user product name to be removed from the product list
private:
	bool testNum(unsigned int num, const Client &C);
	//checks if ID number exists in the file
	bool testText(const string &c_name);
	//checks if the string only contains letters and spaces (used for product input)
	bool testDate(const string &date);
	//checks if string contains only numbers and if it is null
};

#endif // !INPUT_ASKER_H
