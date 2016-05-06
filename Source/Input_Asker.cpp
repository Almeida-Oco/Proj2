#include "..\Headers\Input_Asker.h"

//====================================================================================
//==================================== CLIENTS =======================================
//====================================================================================

int Input_Asker::ask_c_number() const
{
	int c_number;
	do
	{
		cout << "Insert client number" << endl;
		cin >> c_number;
		cin.ignore(9999, '\n');
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "Insert client number" << endl;
			cin >> c_number;
		}
	} while (!testNum(c_number));

		return c_number;
}

int Input_Asker::askClientName() const
{
	bool found = false;
	string client_name;
	do
	{
		cout << "Insert client name : " << endl;
		getline(cin, client_name);
		for (Client_t client_line : Client::instance()->getInfo())
		{
			if (client_line.name == client_name)
			{
				found = true;
				return client_line.number;
			}
		}
		if (!found)
			cout << "Client not found, please try again" << endl;
	} while (!found);
	return -1;
}

bool Input_Asker::testNum(unsigned int num) const
{
	for (Client_t i : Client::instance()->getInfo())
	{
		if (i.number == num)
			return true;
	}
	return false;
}

//====================================================================================
//==================================== DATE =========================================
//====================================================================================

Date_t Input_Asker::askDate(int question) const
{
	int cont = 0, date_placeholder = 0;
	bool done = false;
	vector<string> date_numbers;
	Date_t input_date;
	string line;
	do
	{
		if (question == 0)
			cout << "Please insert the lower bound : (DD/MM/YY) " << endl;
		else if (question == 1)
			cout << "Please insert the upper bound : (DD/MM/YY)" << endl;
		else if (question == 2)
			cout << "Please insert the desired day : (DD/MM/YY)" << endl;
		getline(cin, line);

		date_numbers = string_split(line, "/");
		for (unsigned int i = 0; i < date_numbers.size(); i++)
			date_numbers.at(i) = trim(date_numbers.at(i));
		if (date_numbers.size() == 3)
		{
			input_date.day = stoi(date_numbers.at(0));
			input_date.month = stoi(date_numbers.at(1));
			input_date.year = stoi(date_numbers.at(2));
		}
	} while (!testDate(input_date));

	return input_date;
}

bool Input_Asker::testDate(const Date_t &D) const //tests if the string contains only number, bars '/'  and spaces
{
	if (D.year >= 1)
		if (D.month >= 1 && D.month <= 12)
			if (D.day >= 1 && D.day <= n_days(D.month, D.year))
				return true;
	return false;
}

unsigned int Input_Asker::n_days(const unsigned int M, const unsigned int Y) const 
{
	if (M == JAN || M == MAR || M == MAY || M == JUL || M == AUG || M == OCT || M == DEC)
		return 31;
	else if (M == APR || M == JUN || M == SEP || M == NOV)
		return 30;
	else if (leapYear(Y))
		return 29;
	else
		return 28;
}

bool Input_Asker::leapYear(const unsigned int Y) const
{
	if (remainder(Y, 4) == 0 && remainder(Y, 100) != 0)
		return true;
	else if (remainder(Y, 400) == 0)
		return true;
	else
		return false;
}