#ifndef INPUT_ASKER_H
#define INPUT_ASKER_H

#include <vector>
#include <iostream>
#include <string>
#include "..\Headers\Declarations.h"
#include "..\Headers\Visualize.h"
#include "..\Headers\Client.h"

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

	int askClientName(const vector<Client_t> &info_c);
	//keeps asking client name until an existing one is entered

private:
	bool testNum(unsigned int num, const Client &C);
	//checks if ID number exists in the file
	bool testDate(const Date_t &D) const;
	//checks if string contains only numbers and if it is null
	unsigned int n_days(const unsigned int M, const unsigned int Y) const;
	bool leapYear(const unsigned int Y) const;
};

#endif // !INPUT_ASKER_H
