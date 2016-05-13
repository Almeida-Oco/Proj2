#ifndef INPUT_ASKER_H
#define INPUT_ASKER_H

#include "Declarations.h"
#include "Supermarket.h"
#include <vector>
#include <iostream>
#include <string>

class Supermarket::Input_Asker
{
	static Input_Asker *IA_ptr;

public:
	Input_Asker() {};
	Input_Asker(const Input_Asker &IA) {};

	int ask_c_number()  const;
	//asks for a client number until an existing one is entered

	Date_t askDate(int question) const;
	//input a date using different cout (depending on int question),
	//validates the date and returns the Date struct

	int askClientName() const;
	//keeps asking client name until an existing one is entered

	static Input_Asker *instance()
	{
		if (!IA_ptr)
			IA_ptr = new Input_Asker;
		return IA_ptr;
	}

private:
	bool testNum(unsigned int num) const;
	//checks if ID number exists in the file
	bool testDate(const Date_t &D) const;
	//checks if string contains only numbers and if it is null
	unsigned int n_days(const unsigned int M, const unsigned int Y) const;
	bool leapYear(const unsigned int Y) const;
};

#endif // !INPUT_ASKER_H
